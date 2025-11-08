#pragma once
#include <JuceHeader.h>
#include "AudioPlayer.h"

class clsSpeedSlider : public juce::Component
{
private:
    clsAudioPlayer* AudioPlayer;


public:
    juce::Slider SpeedSlider;

    clsSpeedSlider(clsAudioPlayer& player)
    {
        AudioPlayer = &player;

        SpeedSlider.setSliderStyle(juce::Slider::LinearHorizontal);
        SpeedSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 70, 20);
        SpeedSlider.setNumDecimalPlacesToDisplay(2); 
        SpeedSlider.setTextValueSuffix("x"); 

        SpeedSlider.setNumDecimalPlacesToDisplay(0);
       
        addAndMakeVisible(SpeedSlider);

      
        SpeedSlider.setRange(0, 5, 0.25);
        SpeedSlider.setValue(1);

        
        
    }


    void resized()
    {

        SpeedSlider.setBounds(getLocalBounds());

    }
 
    void SliderHandel()
    {
        if (SpeedSlider.isMouseButtonDown())
        {
            double speedValues[] = { 0.5, 1.0, 1.5, 2.0, 2.25, 2.5 };
            int index = (int)SpeedSlider.getValue(); 
            float selectedSpeed = (float)speedValues[index];

            juce::ResamplingAudioSource* resampleSource = AudioPlayer->getResamplingSource();
            if (resampleSource != nullptr)
                resampleSource->setResamplingRatio(selectedSpeed);

            
            

        }
    }


    
};
