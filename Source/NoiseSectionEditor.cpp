/*
  ==============================================================================

    NoiseSectionEditor.cpp
    Created: 6 Nov 2018 4:44:43pm
    Author:  dfila

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "NoiseSectionEditor.h"

//==============================================================================
NoiseSectionEditor::NoiseSectionEditor(PatSynthAudioProcessor& p) :
	processor(p)
{
	// Setup labels

	m_filterTypeLabel.setText("Filter type", dontSendNotification);
	m_filterTypeLabel.setJustificationType(Justification::centredTop);
	addAndMakeVisible(m_filterTypeLabel);

	m_cutoffLabel.setText("filter freq", dontSendNotification);
	m_cutoffLabel.setJustificationType(Justification::centredTop);
	addAndMakeVisible(m_cutoffLabel);

	m_filterQLabel.setText("filter q", dontSendNotification);
	m_filterQLabel.setJustificationType(Justification::centredTop);
	addAndMakeVisible(m_filterQLabel);

	m_attackLabel.setText("att", dontSendNotification);
	m_attackLabel.setJustificationType(Justification::centredTop);
	addAndMakeVisible(m_attackLabel);

	m_decayLabel.setText("dec", dontSendNotification);
	m_decayLabel.setJustificationType(Justification::centredTop);
	addAndMakeVisible(m_decayLabel);


	// setup filter type combo box
	filterTypeComboBox.addItem(kMenuItemLowPassText,  kMenuItemLowPassId);
	filterTypeComboBox.addItem(kMenuItemHighPassText, kMenuItemHighPassId);
	filterTypeComboBox.addItem(kMenuItemBandPassText, kMenuItemSBandPassId);
	filterTypeComboBox.setJustificationType(Justification::centred);
	addAndMakeVisible(&filterTypeComboBox);
	filterTypeComboBoxAttachment = new ComboBoxAttachment(
		processor.parameters, 
		Globals::paramIdNoiseFilterType, 
		filterTypeComboBox);

	// setup cutoff slider
	filterCutoffSlider.setSliderStyle(Slider::LinearHorizontal);
	filterCutoffSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&filterCutoffSlider);
	filterCutoffSliderAttachment = new SliderAttachment(
		processor.parameters, 
		Globals::paramIdNoiseFilterCutoff,
		filterCutoffSlider);
	filterCutoffSlider.setSkewFactorFromMidPoint(1000.0); // NB: must be after init the attachment ^^^

	// setup resonance slider
	filterResonanceSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	filterResonanceSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&filterResonanceSlider);
	filterResonanceSliderAttachment = new SliderAttachment(
		processor.parameters, 
		Globals::paramIdNoiseFilterReso,
		filterResonanceSlider);

	// setup attack slider
	attackSlider.setSliderStyle(Slider::LinearVertical);
	attackSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&attackSlider);
	attackSliderAttachment = new SliderAttachment(
		processor.parameters,
		Globals::paramIdNoiseAttack,
		attackSlider);

	// setup decay slider
	decaySlider.setSliderStyle(Slider::LinearVertical);
	decaySlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&decaySlider);
	decaySliderAttachment = new SliderAttachment(
		processor.parameters,
		Globals::paramIdNoiseDecay,
		decaySlider);
}

NoiseSectionEditor::~NoiseSectionEditor()
{
}

void NoiseSectionEditor::paint (Graphics& g)
{
	g.setColour(Colours::purple);
	g.fillRect(titleArea);

	g.setColour(Colours::white);
	g.drawText("NOISE", titleArea, Justification::centred);
}

void NoiseSectionEditor::resized()
{
	// Update rectangles sizes
	area = getLocalBounds();
	titleArea = area.removeFromTop(kTitleHeight);
	controlsArea = area;
	waveformArea = controlsArea.removeFromTop(kWaveformHeight);
	ampArea = controlsArea.removeFromRight(kAmpWidth);
	miscArea = controlsArea.removeFromRight(kModWidth);

	// Add filter type combobox
	auto filterTypeComboBoxArea = waveformArea.removeFromTop(50);
	filterTypeComboBox.setBounds(filterTypeComboBoxArea.reduced(12.5));

	// Add frequency slider
	auto frequencySliderArea = waveformArea.removeFromTop(50);
	filterCutoffSlider.setBounds(frequencySliderArea.removeFromTop(25));
	m_cutoffLabel.setBounds(frequencySliderArea);



	// Add attack/decay sliders

	{
		auto r = ampArea.removeFromLeft(50);
		m_attackLabel.setBounds(r.removeFromBottom(25));
		attackSlider.setBounds(r);
	}

	{
		auto r = ampArea.removeFromLeft(50);
		m_decayLabel.setBounds(r.removeFromBottom(25));
		decaySlider.setBounds(r);
	}


	// add pitch envelope (rotary) sliders
	auto pitchEnvSlidersArea = miscArea.removeFromRight(75);

	// --
	auto pitchLfoSlidersArea = miscArea.removeFromRight(75);

	auto filterResonanceArea = pitchLfoSlidersArea.removeFromTop(75);
	filterResonanceSlider.setBounds(filterResonanceArea.removeFromTop(60));
	m_filterQLabel.setBounds(filterResonanceArea);

}
