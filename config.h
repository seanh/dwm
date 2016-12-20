/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const char *fonts[] = {
	"terminus:size=10"
};
static const char dmenufont[]       = "terminus:size=10";
static const char normbordercolor[] = "#444444";
static const char normbgcolor[]     = "#222222";
static const char normfgcolor[]     = "#bbbbbb";
static const char selbordercolor[]  = "#005577";
static const char selbgcolor[]      = "#005577";
static const char selfgcolor[]      = "#eeeeee";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ NULL,       NULL,       NULL,       0,            False,       -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = False;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define AltMask Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ 0,                        KEY,      view,           {.ui = 1 << TAG} }, \
	{ AltMask,                  KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY,                   KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|AltMask,         KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]        = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *custom_dmenucmd[] = { "dwm_custom_dmenu",       NULL };
static const char *termcmd[]         = { "st",                     NULL };
static const char *custom_termcmd[]  = { "dwm_terminal",           NULL };
static const char *volumeupcmd[]     = { "dwm_volume_up",          NULL };
static const char *volumedowncmd[]   = { "dwm_volume_down",        NULL };
static const char *volumemutecmd[]   = { "dwm_volume_toggle_mute", NULL };
static const char *audioplaycmd[]    = { "dwm_audio_play",         NULL };
static const char *audionextcmd[]    = { "dwm_audio_next",         NULL };
static const char *audioprevcmd[]    = { "dwm_audio_prev",         NULL };
static const char *audiomediacmd[]   = { "dwm_audio_media",        NULL };
static const char *toolscmd[]        = { "dwm_tools",              NULL };
static const char *homepagecmd[]     = { "dwm_home_page",          NULL };
static const char *mailcmd[]         = { "dwm_mail",               NULL };
static const char *searchcmd[]       = { "dwm_search",             NULL };
static const char *explorercmd[]     = { "dwm_explorer",           NULL };
static const char *calculatorcmd[]   = { "dwm_calculator",         NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ 0,                            XK_Super_R,spawn,          {.v = custom_dmenucmd } },
	{ MODKEY,                       XK_o,      spawn,          {.v = custom_dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|AltMask,               XK_Return, spawn,          {.v = custom_termcmd } },
	{ MODKEY,                       XK_n,      spawn,          {.v = custom_termcmd } },
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
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_F1,                     0)
	TAGKEYS(                        XK_F2,                     1)
	TAGKEYS(                        XK_F3,                     2)
	TAGKEYS(                        XK_F4,                     3)
	TAGKEYS(                        XK_F5,                     4)
	TAGKEYS(                        XK_F6,                     5)
	TAGKEYS(                        XK_F7,                     6)
	TAGKEYS(                        XK_F8,                     7)
	TAGKEYS(                        XK_F9,                     8)
	TAGKEYS(                        XK_F10,                    9)
	TAGKEYS(                        XK_F11,                    10)
	TAGKEYS(                        XK_F12,                    11)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
    { 0,                            XF86XK_AudioRaiseVolume, spawn,         {.v = volumeupcmd } },
    { 0,                            XF86XK_AudioLowerVolume, spawn,         {.v = volumedowncmd } },
    { 0,                            XF86XK_AudioMute,        spawn,         {.v = volumemutecmd } },
    { 0,                            XF86XK_AudioPlay,        spawn,         {.v = audioplaycmd } },
    { 0,                            XF86XK_AudioPrev,        spawn,         {.v = audionextcmd } },
    { 0,                            XF86XK_AudioNext,        spawn,         {.v = audioprevcmd } },
    { 0,                            XF86XK_AudioMedia,       spawn,         {.v = audiomediacmd } },
    { 0,                            XF86XK_Tools,            spawn,         {.v = toolscmd } },
    { 0,                            XF86XK_HomePage,         spawn,         {.v = homepagecmd } },
    { 0,                            XF86XK_Mail,             spawn,         {.v = mailcmd } },
    { 0,                            XF86XK_Search,           spawn,         {.v = searchcmd } },
    { 0,                            XF86XK_Explorer,         spawn,         {.v = explorercmd } },
    { 0,                            XF86XK_Calculator,       spawn,         {.v = calculatorcmd } },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY|ShiftMask,         Button1,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

