#pragma once
#include <JuceHeader.h>
#include "AudioPlayer.h"

class clsStartButton : public juce::Component
{
private:
    juce::AudioTransportSource transportSource;
    clsAudioPlayer* AudioPlayer;
    std::unique_ptr<juce::Drawable> StartSVG;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(clsStartButton)

public:

    //juce::TextButton StartButton;
    juce::DrawableButton StartButton{ "Start", juce::DrawableButton::ImageRaw };
    clsStartButton(clsAudioPlayer& Player)
    {

        AudioPlayer = &Player;
        StartSVG = juce::Drawable::createFromImageData(
            BinaryData::start_svg,
            BinaryData::start_svgSize
        );

        if (StartSVG != nullptr)
        {
            
            juce::Rectangle<float> buttonArea(0, 0, 40.0f, 40.0f);

            
           StartSVG->replaceColour(juce::Colours::black, juce::Colours::lightgrey); // optional
            StartSVG->setTransformToFit(buttonArea, juce::RectanglePlacement::centred);

            StartButton.setImages(StartSVG.get());
        }
        addAndMakeVisible(StartButton);
    }
  
    void resized()
    {
        StartButton.setBounds(getLocalBounds());
    }

    void HandleClick()
    {
        AudioPlayer->startAudio();
    }
};