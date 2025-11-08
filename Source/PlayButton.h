
#pragma once
#include <JuceHeader.h>
#include "AudioPlayer.h"

class clsPlayButton : public juce::Component
{
private:

   
    clsAudioPlayer* AudioPlayer;

    std::unique_ptr<juce::Drawable> PlaySVG;
    
   
    

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(clsPlayButton);

public:

   
    juce::DrawableButton PlayButton{ "Play", juce::DrawableButton::ImageRaw };
   

    clsPlayButton(clsAudioPlayer& Player)
    {
        AudioPlayer = &Player;
        juce::Rectangle<float> buttonArea(0, 0, 40.0f, 40.0f);
        PlaySVG= juce::Drawable::createFromImageData(BinaryData::circleplay_svg, BinaryData::circleplay_svgSize);
        PlaySVG->replaceColour(juce::Colours::black, juce::Colours::lightgrey);
        PlaySVG->setTransformToFit(buttonArea, juce::RectanglePlacement::centred);
        PlayButton.setImages(PlaySVG.get());
     
       addAndMakeVisible(PlayButton);

        
        
    }

    void resized()
    {
        PlayButton.setBounds(getLocalBounds());
      

    }


    void HandleClick()
    {
        if (!AudioPlayer->GetLength() || AudioPlayer->GetPosition() >= AudioPlayer->GetLength())
            AudioPlayer->SetPosition(0.0);
        AudioPlayer->PlayAudio();

          
    }
    

};
