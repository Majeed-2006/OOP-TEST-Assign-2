#pragma once
#include <JuceHeader.h>
#include "AudioPlayer.h"

class clsPlayStopButton : public juce::Component
{
private:
    juce::AudioTransportSource transportSource;
    clsAudioPlayer* AudioPlayer;

    std::unique_ptr<juce::Drawable> PlaySVG;
    std::unique_ptr<juce::Drawable> StopSVG;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(clsPlayStopButton)

public:
    
    juce::DrawableButton PlayStopButton{ "PlayStop", juce::DrawableButton::ImageRaw };

    clsPlayStopButton(clsAudioPlayer& Player)
    {
        AudioPlayer = &Player;
        PlaySVG = juce::Drawable::createFromImageData(BinaryData::circleplay_svg,BinaryData::circleplay_svgSize );
        StopSVG = juce::Drawable::createFromImageData(BinaryData::pause_svg, BinaryData::pause_svgSize );

        if (PlaySVG != nullptr && StopSVG !=nullptr)
        {
         
            juce::Rectangle<float> buttonArea(0, 0, 40.0f, 40.0f);

            
            PlaySVG->setTransformToFit(buttonArea, juce::RectanglePlacement::centred);
            StopSVG->setTransformToFit(buttonArea, juce::RectanglePlacement::centred);
           PlayStopButton.setImages(PlaySVG.get());
        }
        addAndMakeVisible(PlayStopButton);
    }



    void resized()
    {
        PlayStopButton.setBounds(0, 0, getWidth(), getHeight());
    }

    void HandleClick(bool Playing)
    {
        if (Playing)
        {
            PlayStopButton.setImages(StopSVG.get(), nullptr, nullptr, PlaySVG.get());
            //PlayStopButton.setImages(PlaySVG.get());
            AudioPlayer->StopAudio();
        }
        else
        {
            PlayStopButton.setImages(StopSVG.get(), nullptr, nullptr, PlaySVG.get());
           // PlayStopButton.setImages(StopSVG.get());
            if (!AudioPlayer->GetLength() || AudioPlayer->GetPosition() >= AudioPlayer->GetLength())
                AudioPlayer->SetPosition(0.0);
            AudioPlayer->PlayAudio();

        }
    }
};