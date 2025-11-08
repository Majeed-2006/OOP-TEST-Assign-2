#include "WaveformDisplay.h"    
clsWaveformDisplay::clsWaveformDisplay(clsAudioPlayer& Player):
	AudioPlayer(&Player),
    thumbnailCache(5),
    thumbnail(512, *(AudioPlayer->getFormatManager()), thumbnailCache)
{
    AudioPlayer->addChangeListener(this);
    thumbnail.addChangeListener(this);
    startTimerHz(30);
}
void clsWaveformDisplay::onFileLoaded(const juce::File& file) {
    thumbnail.setSource(new juce::FileInputSource(file));
    repaint();
}

void clsWaveformDisplay::paint(juce::Graphics& g)
{
    auto* transport = AudioPlayer->getTransportSource();
    double current = transport->getCurrentPosition();
    double total = transport->getLengthInSeconds();
    double remaining = total - current;

    auto formatTime = [](double t) -> juce::String {
        int totalSeconds = (int)t;
        int minutes = totalSeconds / 60;
        int seconds = totalSeconds % 60;
        return juce::String(minutes).paddedLeft('0', 2) + ":" +
            juce::String(seconds).paddedLeft('0', 2);
        };

    
    

    
    int boxWidth = 80;
    int boxHeight = 25;

    
    int startX = 0;
    int endX = getWidth() ;

    juce::Rectangle<int> waveformArea(startX, 0, endX - startX, getHeight());

   
   
    
    if (thumbnail.getTotalLength() > 0.0)
    {
        g.saveState();
        g.reduceClipRegion(waveformArea);

       
        
        g.setColour(juce::Colours::skyblue);
        thumbnail.drawChannel(
            g, waveformArea,
            0.0, thumbnail.getTotalLength(), 0, 3.0f
        );

        
        if (total > 0.0)
        {
            float playheadX =
                (float)((current / total) * waveformArea.getWidth())
                + waveformArea.getX();

            g.setColour(juce::Colours::red);
            g.drawLine(
                playheadX, waveformArea.getY(),
                playheadX, waveformArea.getBottom(), 2.0f
            );
        }

        g.restoreState();
    }
    else
    {
        g.setColour(juce::Colours::grey);
        g.drawText("No file loaded",
            waveformArea, juce::Justification::centred);
    }
}


void clsWaveformDisplay::timerCallback() {
    if (!isDragging)
        repaint();

}
void clsWaveformDisplay::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == AudioPlayer)
    {
        onFileLoaded(AudioPlayer->getLastLoadedFile());
    }
    else
    {
        repaint();
    }
}
void clsWaveformDisplay::mouseDown(const juce::MouseEvent& event)
{
    isDragging = true;
    mouseDrag(event);
}
void clsWaveformDisplay::mouseDrag(const juce::MouseEvent& event)
{
    if (thumbnail.getTotalLength() <= 0) return;

    int startX = 100;
    int endX = getWidth() - 100;

    juce::Rectangle<int> waveformArea(
        startX, 0,
        endX - startX,
        getHeight()
    );

    
    float x = juce::jlimit((float)waveformArea.getX(), (float)waveformArea.getRight(), (float)event.x);

    double ratio = (x - waveformArea.getX()) / (double)waveformArea.getWidth();
    double newTime = ratio * AudioPlayer->getTransportSource()->getLengthInSeconds();

    AudioPlayer->getTransportSource()->setPosition(newTime);
    repaint();
}


void clsWaveformDisplay::mouseUp(const juce::MouseEvent&)
{
    isDragging = false;
}
