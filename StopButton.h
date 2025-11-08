
#pragma once
#include <JuceHeader.h>
#include "AudioPlayer.h"

class clsStopButton : public juce::Component
{
private:
   
    clsAudioPlayer *AudioPlayer;
   
    std::unique_ptr<juce::Drawable> StopSVG;
  

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(clsStopButton)

public:
   juce::DrawableButton StopButton{ "Play", juce::DrawableButton::ImageRaw };

  
    
    clsStopButton(clsAudioPlayer& Player)
    {
       
        AudioPlayer = &Player;
       
        juce::Rectangle<float> buttonArea(0, 0, 40.0f, 40.0f);
        StopSVG = juce::Drawable::createFromImageData(BinaryData::pause_svg, BinaryData::pause_svgSize);
        StopSVG->replaceColour(juce::Colours::black, juce::Colours::lightgrey);
        StopSVG->setTransformToFit(buttonArea, juce::RectanglePlacement::centred);
        StopButton.setImages(StopSVG.get());
        addAndMakeVisible(StopButton);
    }

    void resized()
    {
        StopButton.setBounds(getLocalBounds());;


           
    
    }
   
    void HandleClick()
    {

        AudioPlayer->StopAudio();
    }

};
