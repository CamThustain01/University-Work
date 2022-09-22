#include <LeafNode.h>
#include <FallbackSelector.h>
#include <SequenceSelector.h>
#include <Decorator.h>
#include <Blackboard.h>
#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono>
#include <ctime>
#include <stdlib.h>
#include <Windows.h>



enum feelings_ { //feeling enum for fsm

		Happy = 0,
		Sad = 1,
		Scared = 2,
		Angry = 3,
		Disgusted = 4,
		Cautious = 5,
		Romantic = 6,
		Ecstatic = 7,
		Enraged = 8
};




const char* feelings[9] = {"Happy", "Sad", "Scared", "Angry", "Disgusted", "Cautious","Romantic", "Ecstatic","Enraged"}; //array of chars for every feeling the npc could possibly feel

int counter = 0;  //counter for changing the npc's feelings
int decrement = 10; //decrement for changing feelings
int key_pressed = 0; //integer called key pressed this is to close program if key is pressed twice.
int bt_q_pressed = 0; //variable for unique feeling in behavior tree
int bt_w_pressed = 0;




BT::NodeStatus leafStandFunction(BT::TreeNode* owner)
{

	if (BT::Blackboard::getInstance()->getAndDeleteValue("disturbance")) {
		return BT::NodeStatus::NODE_FAILURE;
	}

	//sad to happy
	if (decrement == 5 && counter == 2) //if the decrement is 5 and counter (feeling) is scared change feeling to cautious 
	{
		counter = 5; //cautious
	}
	if (decrement == 0 && counter == 5)//if the decrement is 0 and counter (feeling) is cautious change feeling to happy
	{
		counter = 0; //happy
	}

	//angry to happy
	if (decrement == 5 && counter == 3)//if the decrement is 5 and counter (feeling) is angry change feeling to sad
	{
		counter = 1; //sad
	}
	if (decrement == 0 && counter == 1)//if the decrement is 0 and counter (feeling) is sad change feeling to happy
	{
		counter = 0; //happy
	}

	//ecstatic to sad
	if (decrement == 5 && counter == 7)//if the decrement is 5 and counter (feeling) is ecstatic change feeling to cautious
	{
		counter = 5; //cautious 
	}
	if (decrement == 0 && counter == 5)//if the decrement is 0 and counter (feeling) is ecstatic change feeling to sad
	{
		counter = 1; //sad
	}

	//romantic to disgusted
	if (decrement == 5 && counter == 6)//if the decrement is 0 and counter (feeling) is romantic change feeling to disgusted
	{
		counter = 4;//disgusted
	}

	std::cout << "NPC standing still and feeling " << feelings[counter] << std::endl; //outputs the npcs current feelings when they are standing still 
	decrement -= 1;//takes one away from decrement 

		
	return BT::NodeStatus::NODE_RUNNING;
}

BT::NodeStatus leafTalkingFunction(BT::TreeNode* owner)
{
	if (BT::Blackboard::getInstance()->getAndDeleteValue("disturbance")) {
		return BT::NodeStatus::NODE_FAILURE;
	}

	std::cout << "NPC talking" << std::endl;//ouputs another activity the npc does doesnt effect feelings 

	return BT::NodeStatus::NODE_RUNNING;
}




void run_tree()
{

	//create root and main branch
	BT::FallbackSelector root("rootNode");
	BT::FallbackSelector branch1("mainBranch");

	//add child nodes to root
	root.addChildNode(&branch1);


	//create sequence selector
	BT::SequenceSelector npcBranch("npc");
	BT::SequenceSelector exploreBranch("explore");

	//add child nodes to main branch
	branch1.addChildNode(&npcBranch);
	branch1.addChildNode(&exploreBranch);


	//create decorator
	BT::Decorator leafDecorOne("timerInsert", 0);
	BT::Decorator leafDecorTwo("timerInsert", 0);


	//add decorators to the npc branch
	npcBranch.addChildNode(&leafDecorOne);
	npcBranch.addChildNode(&leafDecorTwo);

	//create leafs one for standing function, the other for talking function
	BT::LeafNode leafOne("Standing", leafStandFunction);
	BT::LeafNode leafTwo("Talking", leafTalkingFunction);

	//add leafs to decorator
	leafDecorOne.addChildNode(&leafOne);
	leafDecorTwo.addChildNode(&leafTwo);

	while (true) //while true
	{

		if (_kbhit()) //check for key board hits
		{
			char input_char = _getch();

			if (input_char == 81 || input_char == 113)//if user presses key q or Q do the following...
			{
				std::cout << "\n";
				std::cout << "You scared the npc!" << std::endl;
				BT::Blackboard::getInstance()->addNewValue("disturbance", 0);
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				counter += 2; //feeling scared
				bt_q_pressed++;//for button combo check
			}
		

			if (input_char == 87 || input_char == 119) //if user presses key w or W do the following...
			{
				std::cout << "\n";
				std::cout << "You shouted at the npc!" << std::endl;
				BT::Blackboard::getInstance()->addNewValue("disturbance", 0);
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				counter += 3; //feeling angry
				bt_w_pressed++;//for button combo check
			}
			if (input_char == 69 || input_char == 101)//if user presses key e or E do the following...
			{
				std::cout << "\n";
				std::cout << "You proposed a deal with the npc!" << std::endl;
				BT::Blackboard::getInstance()->addNewValue("disturbance", 0);
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				counter += 7; //feeling ecstatic
			}
			if (input_char == 82 || input_char == 114)//if user presses key r or R do the following...
			{
				std::cout << "\n";
				std::cout << "You flirted with the npc!" << std::endl;
				BT::Blackboard::getInstance()->addNewValue("disturbance", 0);
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				counter += 6;//feeling romantic

			}
			if (bt_q_pressed >= 1 && bt_w_pressed >= 1)
			{
				std::cout << "\n";
				std::cout << "Thats just cruel..." << std::endl;
				std::cout << "NPC standing still and feeling Enraged" <<std::endl;//feeling enraged output message here as if user was to press two keys program would end before displaying this message

			}

			key_pressed++;//add one to key pressed

		}
	
		

		BT::NodeStatus result = root.tick();

		if (result == BT::NodeStatus::NODE_SUCCESS)
		{
			root.reset();

		}
		else if (result == BT::NodeStatus::NODE_FAILURE || key_pressed >= 2)//if the node status is failure or the key pressed is greater than or equal to 2 do the following...
		{
			std::cout << "The npc ran off!" << std::endl;//ouputs the following
			break;//break
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(110));//cause delay between message output
	}


}

void npc_feeling_msg(int counter)
{
	//sad to happy
	if (decrement < 5 && counter == 2) //if the decrement is 5 and counter (feeling) is scared change feeling to cautious 
	{
		counter = 5; //cautious
	}
	if (decrement >= 5 && counter == 5)//if the decrement is 0 and counter (feeling) is cautious change feeling to happy
	{
		counter = 0; //happy
	}

	//angry to happy
	if (decrement < 5 && counter == 3)//if the decrement is 5 and counter (feeling) is angry change feeling to sad
	{
		counter = 1; //sad
	}
	if (decrement >= 5 && counter == 1)//if the decrement is 0 and counter (feeling) is sad change feeling to happy
	{
		counter = 0; //happy
	}

	//ecstatic to sad
	if (decrement < 5 && counter == 7)//if the decrement is 5 and counter (feeling) is ecstatic change feeling to cautious
	{
		counter = 5; //cautious 
	}
	if (decrement >= 5 && counter == 5)//if the decrement is 0 and counter (feeling) is ecstatic change feeling to sad
	{
		counter = 1; //sad
	}

	//romantic to disgusted
	if (decrement  <= 10 && counter == 6)//if the decrement is 0 and counter (feeling) is romantic change feeling to disgusted
	{
		counter = 4;//disgusted
	}

	std::cout << "The NPC is standing still and feeling " << feelings[counter] << std::endl;//outputs the npcs current activity and how they are feelings
	std::this_thread::sleep_for(std::chrono::milliseconds(500));//cause a delay between messages so it is almost the same time displaying as the behaviour tree messages
	std::cout << "NPC is talking" << std::endl;//outputs message, same as behaviour tree this doesnt effect feelings its for 
	std::this_thread::sleep_for(std::chrono::milliseconds(500));//causes delay between messages so it is almost the same time displaying as the behaviour tree messages 

	decrement -= 1;//takes one away from decrement after the message has been displayed!
}

int exit_application(int key_count) //exit application function takes integer called key_count
{
	if (key_count >= 2) //if the variable is greater than or equal to 2 
	{
		std::cout <<"NPC has run off!\n";//output the message
		exit(0);
	}
	
	
}

void run_fsm() //function for finite state machine
{

	int q_pressed = 0;
	int w_pressed = 0;
	int key_pressed = 0;//variable type integer called key_pressed set to 0, increased by one after a key press in fsm
	bool running = true;//boolean called running, initially set to true. used to continously display npcs behaviour similar to the behaviour tree

	std::cout << "Running Finite State Machine" << std::endl;//output message
	std::cout << "\n";

	feelings_ npc_feelings; //creates an instance of the enum called npc_feelings
	int feeling_switch = 0; //variable called feeling_switch initially set to 0, this is for changing switch statement
	
	while (running) {

		npc_feeling_msg(feeling_switch);//displays the inital npc messages


		switch (feeling_switch)//switch statement for going through each type of feeling in the enum...
		{
		case 1:
			npc_feelings = Sad;
			npc_feeling_msg(feeling_switch);
			break;
		case 2:
			npc_feelings = Scared;
			npc_feeling_msg(feeling_switch);

			break;
		case 3:
			npc_feelings = Angry;
			npc_feeling_msg(feeling_switch);
			break;
		case 4:
			npc_feelings = Disgusted;
			npc_feeling_msg(feeling_switch);
			break;
		case 5:
			npc_feelings = Cautious;
			npc_feeling_msg(feeling_switch);
			break;
		case 6:
			npc_feelings = Romantic;
			npc_feeling_msg(feeling_switch);
			break;
		case 7:
			npc_feelings = Ecstatic;
			npc_feeling_msg(feeling_switch);
			break;
		case 8:
			npc_feelings = Enraged;
			break;
		}


		if (_kbhit())
		{
			char input_char = _getch();

			if (input_char == 81 || input_char == 113)//if user presses key q or Q do the following...
			{
				std::cout<<"\n";
				std::cout << "You scared the npc!" << std::endl;
				feeling_switch = 2; //feeling scared
				key_pressed++;//adds one to key pressed
				q_pressed++;//adds one to this variable
			}


			if (input_char == 87 || input_char == 119) //if user presses key w or W do the following...
			{
				std::cout << "\n";
				std::cout << "You shouted at the npc!" << std::endl;
				feeling_switch = 3; //feeling angry
				key_pressed++;
				w_pressed++;
				
			}


			if (input_char == 69 || input_char == 101)//if user presses key e or E do the following...
			{
				std::cout << "\n";
				std::cout << "You proposed a deal with the npc!" << std::endl;
				feeling_switch = 7; //feeling ecstatic
				key_pressed++;
				
			}

			if (input_char == 82 || input_char == 114)//if user presses key r or R do the following...
			{
				std::cout << "\n";
				std::cout << "You flirted with the npc!" << std::endl;
				feeling_switch = 6; //feeling romantic
				key_pressed++;
			
			}
			if (q_pressed == 1 && w_pressed == 1)
			{
				std::cout << "\n";
				std::cout << "Thats just cruel..." << std::endl;
				feeling_switch = 8;
				npc_feeling_msg(feeling_switch);
			}

			exit_application(key_pressed); //exits application if a key has been pressed 2 or more times

		}



	}
	
}



int main(int argc, char** argv) {


	int user_choice = 0;//integer for user choice, user can choose two options finite state machine or behaviour tree

	//output messages for the user to understand the program
	std::cout << "NPC Action/Dialogue System\n\n";
	std::cout << "Pick An AI method:\n\n";
	std::cout << "1) Finite State Machines\n2) Behaviour Tree\n\n";
	std::cout << "Action Options (note these down or keep README open)\n";
	std::cout << "Q - Scare, W - shout, E - Trade, R - Flirt\n";
	std::cout << "Press 1 or 2\n";

	std::cin >> user_choice;//add user input into variable

	switch (user_choice)//switch statement for running each ai method
	{
	case 1: //if 1 run the following 
		std::cout << "FSM Running\n";//output 
		run_fsm(); //run fsm code..
		break;
	case 2:
		std::cout << "Behaviour Tree Running\n";//output
		run_tree(); //run behaviour tree...
		break;
	default:
		//if user press anything other than 1 or 2 make them pick again
		std::cout << "Not a valid choice!\n";
		std::cout << "Quitting Application!\n";
		break;
	}

}