/* A52PreferencesWindowController */

#import <Cocoa/Cocoa.h>

@interface A52Preferences : NSObject <NSWindowDelegate>
{
	IBOutlet NSWindow					*window_mainWindow;
	IBOutlet NSPopUpButton				*popup_ac3DynamicRangeType;
	IBOutlet NSPopUpButton				*popup_OutputMode;
	
	IBOutlet NSWindow					*window_dynRangeSheet;
    IBOutlet NSTextField                *textField_ac3DynamicRangeValue;
    IBOutlet NSSlider                   *slider_ac3DynamicRangeSlider;
	
	NSUserDefaults						*defaults;
	float								dynValue;
	float								savedDynValue;
	int									twoChannelMode;
}
@property (retain) NSUserDefaults *defaults;
@property float dynValue;
@property float savedDynValue;
@property int twoChannelMode;

- (IBAction)setAC3DynamicRangePopup:(id)sender;
- (IBAction)set2ChannelModePopup:(id)sender;

- (IBAction)setAC3DynamicRangeValue:(id)sender;
- (IBAction)setAC3DynamicRangeSlider:(id)sender;
- (IBAction)cancelDynRangeSheet:(id)sender;
- (IBAction)saveDynRangeSheet:(id)sender;

- (IBAction)cancel:(id)sender;
- (IBAction)save:(id)sender;
@end
