#include <X11/XF86keysym.h>

/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
//static const char *fonts[]          = { "monospace:size=10" };
static const char *fonts[]          = { "monospace:size=10:style=Bold" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
//static const char col_cyan[]        = "#005577";
static const char col_cyan[]        = "#4477bb";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      						instance    		title       			tags mask     isfloating   monitor */
	{ "firefox",  						"Navigator",		NULL,       			1 << 1,       	0,           -1 },
	{ "konsole",  						NULL,       		NULL,       			1 << 0,       	0,           -1 },
	{ "kakaotalk.exe",  				NULL,       		NULL,       			1 << 5,       	1,           -1 },
	{ "dolphin",  						NULL,       		NULL,       			1 << 3,       	0,           -1 },
	{ NULL,  							NULL,  				"LibreOffice", 			1 << 6,       	0,           -1 },
	{ "hwp.exe",  						NULL,  				NULL, 					1 << 6,       	0,           -1 },
	{ "hwp",  							NULL,  				NULL, 					1 << 6,       	0,           -1 },
	{ "Code",  							NULL,  				NULL, 					1 << 4,       	0,           -1 },
	{ "Steam",  						NULL,  				NULL, 					1 << 7,       	0,           -1 },
	{ "Pavucontrol",  					NULL,       		NULL,       			0,      		1,           -1 },
	{ "Blueman-manager",  				NULL,       		NULL,       			0,      		1,           -1 },
	{ "firefox",  						"Toolkit",       	"화면 속 화면", 	   	0,      		1,           -1 },
	{ "System-config-printer.py",  		NULL,       		NULL,       			0,      		1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* dir */
static const char rofi_clipboard_rasi[] = "~/dwm/rofi/clipboard.rasi";
static const char rofi_powermenu_rasi[] = "~/dwm/rofi/powermenu.rasi";
static const char rofi_drunmenu_rasi[] = "~/dwm/rofi/config.rasi";

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *roficmd[] = { "rofi", "-show", "drun", "-theme", rofi_drunmenu_rasi, NULL };
static const char *termcmd[]  = { "konsole", NULL };
static const char *clipcmd[]  = { "rofi", "-modi", "\"clipboard:greenclip print\"", "-show", "clipboard", "-theme", rofi_clipboard_rasi, NULL };

static const char *unmutevol[]  = { "pactl", "set-sink-mute", "@DEFAULT_SINK@", "0", NULL };
static const char *raisevol[]  = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%", NULL };
static const char *lowervol[]  = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%", NULL };
static const char *togglevol[]  = { "pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL };

//static const char *refresh[] = { "/home/hanwool/.dwm/refresh_dwmstatus.sh", NULL };
static const char *refresh2[] = { "killall", "-SIGUSR2", "conky", NULL };

//static const char *notifyvol[] = { "/home/hanwool/.dwm/notify_vol.sh", NULL };
//static const char *notifymute[] = { "/home/hanwool/.dwm/notify_mute.sh", NULL };

static const char *briup[] = { "brightnessctl", "set", "5%+", NULL };
static const char *bridown[] = { "brightnessctl", "set", "5%-", NULL };

static const char *powermenu[] = { "/home/hanwool/dwm/scripts/powermenu.sh", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = roficmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_c,      spawn,          {.v = clipcmd } },

	{ 0,         XF86XK_AudioRaiseVolume,      spawn,          {.v = unmutevol } },
	{ 0,         XF86XK_AudioRaiseVolume,      spawn,          {.v = raisevol } },
	{ 0,         XF86XK_AudioRaiseVolume,      spawn,          {.v = refresh2 } },

	{ 0,         XF86XK_AudioLowerVolume,      spawn,          {.v = unmutevol } },
	{ 0,         XF86XK_AudioLowerVolume,      spawn,          {.v = lowervol } },
	{ 0,         XF86XK_AudioLowerVolume,      spawn,          {.v = refresh2 } },

	{ 0,                XF86XK_AudioMute,	   spawn,          {.v = togglevol } },
	{ 0,                XF86XK_AudioMute,	   spawn,          {.v = refresh2 } },

	{ 0,                XF86XK_MonBrightnessUp,        spawn,          {.v = briup } },
    { 0,                XF86XK_MonBrightnessUp,        spawn,          {.v = refresh2 } },

    { 0,                XF86XK_MonBrightnessDown,      spawn,          {.v = bridown } },
    { 0,                XF86XK_MonBrightnessDown,      spawn,          {.v = refresh2 } },

	{ MODKEY,                       XK_Escape, spawn,          {.v = powermenu } },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },

	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	//{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },

	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },

	{ ClkWinTitle,          0,              Button1,        zoom,           {0} },
	{ ClkWinTitle,          0,              Button2,        killclient,           {0} },
	{ ClkWinTitle,          0,              Button3,        togglesticky,           {0} },

	{ ClkStatusText,        0,              Button1,        spawn,          {.v = roficmd } },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = powermenu } },
};

