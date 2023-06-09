/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int gappih    = 5;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 5;       /* vert inner gap between windows */
static const unsigned int gappoh    = 5;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 5;       /* vert outer gap between windows and screen edge */
static int smartgaps                = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {"monospace:size=11:antialias=true:hinting=true",
                                       "JoyPixels:pixelsize=12:antialias=true:autohint=true",
                                       "SymbolsNerdFont:size=11:antialias=true:autohint=true"
						     	};
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "", "", "嗢" , "", "", "", ""};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* Default: Master on left, slaves on right */
	{ "[T]",      bstack },  /* Master on top, slaves on bottom */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
	{ MOD, XK_v,     ACTION##stack, {.i = 0 } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *termcmd[]  = { "st", NULL };

static const Key keys[] = {
    /* modifier                         key                     function                argument */
	STACKKEYS(MODKEY,                                       focus)
	STACKKEYS(MODKEY|ShiftMask,                             push)

    /* Launch programs */
	{ MODKEY,                       XK_d,                   spawn,                  {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,              spawn,                  {.v = termcmd } },
	{ MODKEY,                       XK_F5,                  xrdb,                   {.v = NULL } },

    /* Layouts */
	{ MODKEY,                       XK_t,                   setlayout,              {.v = &layouts[0]} }, /* tile */
	{ MODKEY|ShiftMask,             XK_t,                   setlayout,              {.v = &layouts[1]} }, /* bstack */
	{ MODKEY,                       XK_f,                   setlayout,              {.v = &layouts[2]} }, /* float */
	{ MODKEY|ShiftMask,             XK_f,                   togglefloating,         {0} },

    /* Layout manipulation */
	{ MODKEY,                       XK_s,                   togglesticky,           {0} },
	{ MODKEY,                       XK_b,                   togglebar,              {0} },
	{ MODKEY,                       XK_i,                   incnmaster,             {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,                   incnmaster,             {.i = -1 } },
	{ MODKEY,                       XK_h,                   setmfact,               {.f = -0.05} },
	{ MODKEY,                       XK_l,                   setmfact,               {.f = +0.05} },
	{ Mod1Mask,                     XK_q,                   killclient,             {0} },
	{ MODKEY,                       XK_a,                   togglegaps,             {0} },
	{ MODKEY|ShiftMask,             XK_a,                   defaultgaps,            {0} },

  { MODKEY,                       XK_0,                   view,                   {.ui = ~0 } },
	{ MODKEY,                       XK_0,                   tag,                    {.ui = ~0 } },

	{ Mod1Mask,                     XK_Return,              zoom,                   {0} },
	{ MODKEY,                       XK_Tab,                 view,                   {0} },
	{ MODKEY,                       XK_Left,                focusmon,               {.i = -1 } },
	{ MODKEY,                       XK_Right,               focusmon,               {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Left,                tagmon,                 {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Right,               tagmon,                 {.i = +1 } },

    /* Tagkeys */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)

    /* Restart or quiet dwm */
	{ Mod1Mask|ShiftMask,           XK_q,                   quit,                   {0} },
	{ Mod1Mask|ShiftMask,           XK_r,                   quit,                   {1} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
  { ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

