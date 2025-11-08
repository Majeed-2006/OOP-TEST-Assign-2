#include "PlaylistRowComponent.h"

clsPlaylistRowComponent::clsPlaylistRowComponent(const juce::String& trackName,
    std::function<void()> onPlayClick,
    std::function<void()> onDeleteClick)
{
    trackLabel.setText(trackName, juce::dontSendNotification);
    trackLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    addAndMakeVisible(trackLabel);

    playButton.onClick = onPlayClick;
    addAndMakeVisible(playButton);

    deleteButton.onClick = onDeleteClick;
    deleteButton.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
    addAndMakeVisible(deleteButton);
}

void clsPlaylistRowComponent::resized()
{
    auto area = getLocalBounds();
    trackLabel.setBounds(area.removeFromLeft(area.getWidth() - 120));
    playButton.setBounds(area.removeFromLeft(60).reduced(2));
    deleteButton.setBounds(area.reduced(2));
}
