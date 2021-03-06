
/*
 AfterDarkGestalt.h
 All Gestalt selectors that are defined by After Dark.

 Copyright c 1990-93 Berkeley Systems, Inc.
 5/20/93
*/

#ifndef __AFTER_DARK_GESTALT__
#define __AFTER_DARK_GESTALT__

/*
--------------------------------------------------------------------------------------

 The routines identified here work with After Dark 2.0u (released xxx) and later including

 Star Trek The Screen Saver.  If someone has After Dark they probably have a version
 that supports the Gestalt calls.  If someone has an earlier version of After Dark 2.0
 they can upgrade to the latest version for free by contacting Berkeley Systems.

 Some stuff was added for Star Trek The Screen Saver (released 11/92) and After Dark 2.0x
 (released 1/93).  These have been identified by the define 'AD20x'.  They will not work
 with versions of AD earlier than version 2.0x.


----------------------------------------------------------------------------------------
*/

/* generic screen saver selectors. */

#define gestaltScreenSaverAttr 'SAVR'  /* defined if a screen saver is installed. */

/* Gestalt called with 'SAVR' selector returns longword bitmask. Here are the bit numbers: */
enum {
 gestaltSaverTurnedOn = 0,		/* saver enabled/disabled. */
 gestaltSaverAsleep,			/* saver currently asleep. */
 gestaltSaverDemoMode,			/* saver sleeping in demo mode. */
 gestaltSaverPasswordMode,		/* saver sleeping in password-protected mode. */
 gestaltAppDrawingDisabled		/* Quickdraw drawing disallowed between module animation frames. */
};

#define gestaltScreenSaverControl 'SAVC'  /* allows controlling screen saver.*/


/* Gestalt called with 'SAVC' selector returns a pointer to a procedure with the following calling conventions: */
enum SaverCommand {
	eSaverWakeUp,	/*  Make AD wake up. */
	eSaverSleep		/* Make AD go to sleep. */
#ifdef AD20x
	, eSaverOn,		/* Turn AD on.  */
	eSaverOff		/* Turn AD off. */
#endif
	, eForceShort = 257 /* Force the enums to be shorts instead of bytes. */
};

typedef enum SaverCommand SaverCommand;

/*
 This function, called with the parameter eSaverWakeUp, causes the screen saver to wake
 up at the next opportunity.  When called with the parameter eSaverSleep, it causes the saver
 to sleep at the next opportunity.  When called with parameter eSaverOn, it turns the saver on.
 This does not put AD to sleep, it just enables AD so it can go to sleep.  When called with
 the parameter eSaverOff, it turns AD off.  AD will not fall asleep until it is called with
 eSaver.  eSaverOn and eSaverOff are equivalent to using the On/Off switch in the AD
 Control Panel.

 The function returns an error if the action is impossible for some reason.
*/

typedef pascal OSErr (*SaverControlProcPtr) (SaverCommand command); /* pascal conventions! */

/* After Dark specific selectors. */
/* This Gestalt selector returns a longword bitmask containing public information about After Dark. */
#define gestaltAfterDarkAttr 'ADrk'   /* After Dark states. */

enum {
	eSystemIQActive = 0,	/* SystemIQx activity monitor active. */
	eSoundActive,			/* After Dark has allocated a sound channel. */
	eADAcquiringPassword	/* After Dark has its password dialog up. */
};

#ifdef AD20x
/* This Gestalt selector returns a pointer to a procedure that gives the DirID and vRefNum of */
/* the 'After Dark Files' folder where the AD modules live. */

#define gestaltAfterDarkFolder 'ADfd'
typedef pascal Boolean (*ADFolderProc)(short* pVRefNum, long* pDirID); /*
pascal conventions! */
#endif

#endif



