#pragma once
#include <JuceHeader.h>
#include "AudioPlayer.h"

class clsVolumeSlider : public juce::Component
{
private:
    clsAudioPlayer* AudioPlayer;


public:
    juce::Slider VolumeSlider;

    clsVolumeSlider(clsAudioPlayer& player)
    {
        AudioPlayer = &player;
        addAndMakeVisible(VolumeSlider);
        VolumeSlider.setRange(0.0, 1.0, 0.01);
        VolumeSlider.setValue(0.5);
        VolumeSlider.setSliderStyle(juce::Slider::LinearVertical);
        VolumeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);



    }


    void resized()
    {

        VolumeSlider.setBounds(getLocalBounds());

    }
    
    void SliderHandel()
    {
        if (VolumeSlider.isMouseButtonDown())
        {
            AudioPlayer->SetGain((float)VolumeSlider.getValue());
        }
    }



};
