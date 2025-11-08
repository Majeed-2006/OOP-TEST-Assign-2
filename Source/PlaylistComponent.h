#pragma once
#include <JuceHeader.h>
#include "AudioPlayer.h"

class clsPlaylistComponent : public juce::Component, public juce::ListBoxModel, public juce::Button::Listener
{
public:
	clsPlaylistComponent(clsAudioPlayer& player1Ref, clsAudioPlayer& player2Ref);


	void addFile(const juce::File& file);
	int getNumRows() override;
	void paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected) override;
	juce::Component* refreshComponentForRow(int rowNumber, bool isRowSelected, juce::Component* existingComponentToUpdate) override;
	void listBoxItemClicked(int row, const juce::MouseEvent&) override;
	void resized() override;
	void HandleClick();
	void buttonClicked(juce::Button* button) override;
	juce::TextButton addToPlaylistButton{ "Add to Playlist" };

private:
	clsAudioPlayer& player1;
	clsAudioPlayer& player2;
	clsAudioPlayer* targetPlayer; // To determine which player to load into

	// add toggle buttons to select the target player
	juce::ToggleButton deck1Button{ "Deck 1" };
	juce::ToggleButton deck2Button{ "Deck 2" };

	std::vector<juce::File> playlistFiles;   // To store the audio files
	juce::ListBox playlistBox;               // To display the playlist
	juce::Label headerLabel;
	juce::Label headerTitleLabel;
	std::unique_ptr<juce::FileChooser> addToPlaylistChooser;

};