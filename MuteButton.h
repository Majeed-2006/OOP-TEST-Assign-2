#pragma once
#include <JuceHeader.h>
#include "AudioPlayer.h"
#include <functional>

class clsMuteButton : public juce::Component
{
private:
    clsAudioPlayer* AudioPlayer;
    std::function<void()> onToggle;
    std::unique_ptr<juce::Drawable> MuteSVG;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(clsMuteButton)
public:

    //juce::TextButton MuteButton;
    juce::DrawableButton MuteButton{ "Mute", juce::DrawableButton::ImageRaw };
    clsMuteButton(clsAudioPlayer& Player)
    {
        AudioPlayer = &Player;
       MuteSVG = juce::Drawable::createFromImageData(
            BinaryData::NoVolume_svg,
            BinaryData::NoVolume_svgSize
        );

        if (MuteSVG != nullptr)
        {
        
            juce::Rectangle<float> buttonArea(0, 0, 40.0f, 40.0f);

            
            MuteSVG->replaceColour(juce::Colours::black, juce::Colours::lightgrey); // optional
            MuteSVG->setTransformToFit(buttonArea, juce::RectanglePlacement::centred);

            MuteButton.setImages(MuteSVG.get());
        }
        addAndMakeVisible(MuteButton);
    }
  
    void resized()
    {
        
        MuteButton.setBounds(getLocalBounds());
        
    }

    void HandleClick()
    {

        AudioPlayer->MuteUnmute();

        // notify owner (GUI) so it can update the slider UI
        if (onToggle)
            onToggle();
    }

    void SetOnToggle(std::function<void()> cb) 
    { 
        onToggle = std::move(cb);
    } 
};
