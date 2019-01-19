/*
  ==============================================================================

    MasterSectionEditor.cpp
    Created: 6 Nov 2018 3:44:06pm
    Author:  dfila

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MasterSectionEditor.h"

//==============================================================================
MasterSectionEditor::MasterSectionEditor(PatSynthAudioProcessor& p) : 
	processor (p)
{
	// Setup labels
	m_mixLabel.setText("mix", dontSendNotification);
	m_mixLabel.setJustificationType(Justification::centredTop);
	addAndMakeVisible(m_mixLabel);

	m_eqFreqLabel.setText("eq freq", dontSendNotification);
	m_eqFreqLabel.setJustificationType(Justification::centredTop);
	addAndMakeVisible(m_eqFreqLabel);
	
	m_distortLabel.setText("distort", dontSendNotification);
	m_distortLabel.setJustificationType(Justification::centredTop);
	addAndMakeVisible(m_distortLabel);

	m_eqGainLabel.setText("eq gain", dontSendNotification);
	m_eqGainLabel.setJustificationType(Justification::centredTop);
	addAndMakeVisible(m_eqGainLabel);

	m_levelLabel.setText("level", dontSendNotification);
	m_levelLabel.setJustificationType(Justification::centredTop);
	addAndMakeVisible(m_levelLabel);
	
	m_panLabel.setText("pan", dontSendNotification);
	m_panLabel.setJustificationType(Justification::centredTop);
	addAndMakeVisible(m_panLabel);

	// mix slider
	mixSlider.setLookAndFeel (&lookAndFeel);
	mixSlider.setSliderStyle(Slider::LinearHorizontal);
	mixSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&mixSlider);
	mixSliderAttachment = new SliderAttachment(
		processor.parameters,
		Globals::paramIdMasterMix,
		mixSlider);

	// eq freq slider
	eqFreqSlider.setEnabled (false);
	eqFreqSlider.setLookAndFeel (&lookAndFeel);
	eqFreqSlider.setSliderStyle(Slider::LinearHorizontal);
	eqFreqSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&eqFreqSlider);
	eqFreqSliderAttachment = new SliderAttachment(
		processor.parameters,
		Globals::paramIdMasterEqFreq,
		eqFreqSlider);
	
	// distort (rotary) slider
	distortSlider.setLookAndFeel (&lookAndFeel);
	distortSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	distortSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&distortSlider);
	distortSliderAttachment = new SliderAttachment(
		processor.parameters,
		Globals::paramIdMasterDistort,
		distortSlider);

	// eq gain (rotary) slider
	eqGainSlider.setEnabled (false);
	eqGainSlider.setLookAndFeel (&lookAndFeel);
	eqGainSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	eqGainSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&eqGainSlider);
	eqGainSliderAttachment = new SliderAttachment(
		processor.parameters,
		Globals::paramIdMasterEqGain,
		eqGainSlider);

	// level (rotary) slider
	levelSlider.setLookAndFeel (&lookAndFeel);
	levelSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	levelSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&levelSlider);
	levelSliderAttachment = new SliderAttachment(
		processor.parameters,
		Globals::paramIdMasterLevel,
		levelSlider);

	// pan (rotary) slider
	panSlider.setEnabled (false);
	panSlider.setLookAndFeel (&lookAndFeel);
	panSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	panSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	addAndMakeVisible(&panSlider);
	panSliderAttachment = new SliderAttachment(
		processor.parameters,
		Globals::paramIdMasterPan,
		panSlider);
}

MasterSectionEditor::~MasterSectionEditor()
{
}

void MasterSectionEditor::paint (Graphics& g)
{
	g.setColour (Colour (0xFF171717));
	
	auto r = getLocalBounds();

	auto titleArea = r.removeFromTop (kTitleHeight);
	g.fillRect ( titleArea.reduced (3) );

	auto controlsArea = r.reduced (3);
	g.fillRect (controlsArea);



	g.setColour(Colours::white);
	g.drawText("M A S T E R", titleArea, Justification::centred);
}

void MasterSectionEditor::resized()
{
	// Update rectangles sizes
	area = getLocalBounds();
	titleArea = area.removeFromTop(kTitleHeight);
	controlsArea = area;
	waveformArea = controlsArea.removeFromTop(kWaveformHeight);
	ampArea = controlsArea.removeFromRight(kAmpWidth);
	miscArea = controlsArea.removeFromRight(kModWidth);

	// --
	{
		auto r = waveformArea.removeFromTop(50);
		mixSlider.setBounds(r.removeFromTop(25));
		m_mixLabel.setBounds(r);
	}

	// --
	{
		auto r = waveformArea.removeFromTop(50);
		eqFreqSlider.setBounds(r.removeFromTop(25));
		m_eqFreqLabel.setBounds(r);
	}

	// --
	auto eqGainAndPanlidersArea = miscArea.removeFromRight(75);

	{
		auto r = eqGainAndPanlidersArea.removeFromTop(75);
		eqGainSlider.setBounds(r.removeFromTop(60));
		m_eqGainLabel.setBounds(r);
	}

	{
		auto r = eqGainAndPanlidersArea.removeFromTop(75);
		panSlider.setBounds(r.removeFromTop(60));
		m_panLabel.setBounds(r);
	}

	// ---
	auto pitchLfoSlidersArea = miscArea.removeFromRight(75);

	{
		auto r = pitchLfoSlidersArea.removeFromTop(75);
		distortSlider.setBounds(r.removeFromTop(60));
		m_distortLabel.setBounds(r);
	}

	{
		auto r = pitchLfoSlidersArea.removeFromTop(75);
		levelSlider.setBounds(r.removeFromTop(60));
		m_levelLabel.setBounds(r);
	}
}
