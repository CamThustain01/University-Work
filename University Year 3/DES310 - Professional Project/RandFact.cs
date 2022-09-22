using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class RandFact : MonoBehaviour
{

    public int randValue;
    public bool winState;
    public GameObject factDisplay;  

    void Start()
    {
        if (winState == true)
        {
            StartCoroutine(WinFactTrack());
        }

        if (winState == false)
        {
            StartCoroutine(LoseFactTrack());
        }
    }

    IEnumerator WinFactTrack()
    {
        randValue = Random.Range(1,6);

        switch (randValue)
        {
            case 1:
                factDisplay.GetComponent<Text>().text = "Anteaters don’t just eat ants! They also eat termites, and occasionally fruit and bird eggs.";
                break;
            case 2:
                factDisplay.GetComponent<Text>().text = "Anteaters don’t have any teeth!";
                break;
            case 3:
                factDisplay.GetComponent<Text>().text = "There are 4 different species of anteater! There is the giant anteater, the silky anteater, the northern tamandua, and the southern tamandua.";
                break;
            case 4:
                factDisplay.GetComponent<Text>().text = "Anteaters have the lowest body temperature of any mammal, with a core temperature of 32 degrees celsius.";
                break;
            case 5:
                factDisplay.GetComponent<Text>().text = "The anteater's tongue is sticky and covered with spines!";
                break;
        }

        yield return new WaitForSeconds(9);
    }



    IEnumerator LoseFactTrack()
    {
        randValue = Random.Range(1, 6);

        switch (randValue)
        {
            case 1:
                factDisplay.GetComponent<Text>().text = "Wildlife vehicle collisions are harmful to humans too, and cost people £3,825,000 each year in Sao Paolo alone.";
                break;
            case 2:
                factDisplay.GetComponent<Text>().text = "Around 17 anteaters are killed a year per 60 miles of road in some areas.";
                break;
            case 3:
                factDisplay.GetComponent<Text>().text = "Anteaters are 8 times less likely to cross roads than natural obstacles, like streams.";
                break;
            case 4:
                factDisplay.GetComponent<Text>().text = "Urban development has led to anteater growth rates halfing over the last 30 years.";
                break;
            case 5:
                factDisplay.GetComponent<Text>().text = "Half of the land in the Cerrado region has been deforested for use in agriculture. ";
                break;

        }

        yield return new WaitForSeconds(9);
    }
}
