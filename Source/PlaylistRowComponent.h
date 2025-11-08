
#pragma once
#include <JuceHeader.h>

class clsPlaylistRowComponent : public juce::Component
{
public:
    clsPlaylistRowComponent(const juce::String& trackName,
        std::function<void()> onPlayClick,
        std::function<void()> onDeleteClick);

    void resized() override;

private:
    juce::Label trackLabel;
    juce::TextButton playButton{ "Play" };
    juce::TextButton deleteButton{ "Delete" };

};