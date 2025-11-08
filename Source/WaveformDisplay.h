#pragma once
#include <JuceHeader.h>
#include "AudioPlayer.h"

class clsWaveformDisplay : public juce::Component, private juce::ChangeListener, private juce::Timer           // Allows us to periodically repaint the component
{
public:
    bool isDragging = false;

    clsWaveformDisplay(clsAudioPlayer& Player);
    void onFileLoaded(const juce::File& file);
    void mouseUp(const juce::MouseEvent&) override;
    void paint(juce::Graphics& g) override;
    void mouseDown(const juce::MouseEvent& event) override;
    void mouseDrag(const juce::MouseEvent& event) override;
    

private:
    void timerCallback() override;
    void changeListenerCallback(juce::ChangeBroadcaster*) override;

    clsAudioPlayer* AudioPlayer;
    juce::AudioTransportSource* transportSource;
    juce::AudioThumbnailCache thumbnailCache;
    juce::AudioThumbnail thumbnail;
};
