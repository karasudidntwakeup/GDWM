/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>



/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 15;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 15;       /* vert inner gap between windows */
static const unsigned int gappoh    = 15;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 15;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[] = { "Cascadia Mono:size=13", "SF Arabic:size=13","JetBrains Mono:size=11"};
static const char dmenufont[]       = "Cascadia Code:size=13";

static const char norm_fg[] = "#f1f1f1";
static const char norm_bg[] = "#191919";
static const char norm_border[] = "#448cf6";
static const char sel_fg[] = "#f1f1f1";
static const char sel_bg[] = "#191919";
static const char sel_border[] = "#f8708c";
static const char urg_fg[] = "#f1f1f1";
static const char urg_bg[] = "#707070";
static const char urg_border[] = "#707070";
static const char *colors[][3]      = {
    /*               fg           bg         border                         */
    [SchemeNorm] = { norm_fg,     norm_bg,   norm_border }, // unfocused wins
    [SchemeSel]  = { sel_fg,      sel_bg,    sel_border },  // the focused win
    [SchemeUrg] =  { urg_fg,      urg_bg,    urg_border },
};



//


/*sound*/
static const char *upvol[]   = { "/usr/bin/pactl", "set-sink-volume", "0", "+5%",     NULL };
static const char *downvol[] = { "/usr/bin/pactl", "set-sink-volume", "0", "-5%",     NULL };
static const char *mutevol[] = { "/usr/bin/pactl", "set-sink-mute",   "0", "toggle",  NULL };


//


//lock



static const char *slockcmd[] = { "slock", NULL };


//


//brightness


static const char *brightnessup[] = {"sudo", "xbacklight", "-inc","5", NULL };
static const char *brightnessdown[] = {"sudo", "xbacklight", "-dec", "5", NULL };





///tagging */


static const char *tags[] = { "   ", "  表 ", " 地 ", " 新 ", " 女 " };

static const char *tagsel[][2] = {
	{ "#64aefe", "#191919" },
	{ "#f5ce6b", "#191919" },
	{ "#7fa3fa", "#191919" },
	{ "#f78baa", "#191919" },
	{ "#7aa2f7", "#191919" },
	{ "#f28fad", "#191919" },
	{ "#ffffff", "#191919" },
	{ "#b4aefe", "#191919" },
	{ "#f28fad", "#191919" },
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "qutebrowser",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */

static const char *filebrowsercmd[]  = { "pcmanfm", NULL};
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", norm_bg, "-nf", norm_fg, "-sb", sel_bg, "-sf", sel_fg, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *browser[]       = { "librewolf", NULL, "librewolf" };



static const Key keys[] = {
	/* modifier                     key        function        argument */



  { MODKEY,             XK_Return, spawn,          {.v = termcmd } },
        { MODKEY,                       XK_g,      setlayout,      {.v = &layouts[0] } },
        { MODKEY,                       XK_f,      spawn,       {.v = filebrowsercmd } },
        { MODKEY,                       XK_space,  spawn,          {.v = dmenucmd} },
        { MODKEY,                       XK_c,      spawn,       {.v = browser } },

        { MODKEY,                       XK_b,      togglebar,      {0} },
        { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
        { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
        { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
        { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
        { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
        { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
        { MODKEY,             XK_h,      setcfact,       {.f = +0.25} },
        { MODKEY,             XK_l,      setcfact,       {.f = -0.25} },
        { MODKEY,             XK_o,      setcfact,       {.f =  0.00} },
        { MODKEY|ShiftMask,                       XK_Return, zoom,           {0} },
        { MODKEY|Mod1Mask,              XK_u,      incrgaps,       {.i = +1 } },
        { MODKEY|Mod1Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
        { MODKEY|Mod1Mask,              XK_i,      incrigaps,      {.i = +1 } },
        { MODKEY|Mod1Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
        { MODKEY|Mod1Mask,              XK_o,      incrogaps,      {.i = +1 } },
        { MODKEY|Mod1Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
        { MODKEY|Mod1Mask,              XK_6,      incrihgaps,     {.i = +1 } },
        { MODKEY|Mod1Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
        { MODKEY|Mod1Mask,              XK_7,      incrivgaps,     {.i = +1 } },
        { MODKEY|Mod1Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
        { MODKEY|Mod1Mask,              XK_8,      incrohgaps,     {.i = +1 } },
        { MODKEY|Mod1Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
        { MODKEY|Mod1Mask,              XK_9,      incrovgaps,     {.i = +1 } },
        { MODKEY|Mod1Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
        { MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
        { MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
        { MODKEY,                       XK_Tab,    view,           {0} },
        { MODKEY,             XK_x,      killclient,     {0} },
        { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
        { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
        { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
        { MODKEY|ShiftMask,             XK_w,  togglefloating, {0} },
        { MODKEY,                       XK_s,                       spawn,
SHCMD("telegram-desktop") },
        { 0,                            XK_Print,                   spawn,
SHCMD("maim -s -d 1 | xclip -selection clipboard -t image/png -i") },

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
        { MODKEY|ShiftMask,             XK_q,      quit,           {0} },



        { 0,                       XF86XK_AudioLowerVolume, spawn, {.v = downvol } },
        { 0,                       XF86XK_AudioMute, spawn, {.v = mutevol } },
        { 0,                       XF86XK_AudioRaiseVolume, spawn, {.v = upvol   } },




         { 0, XF86XK_MonBrightnessUp,   spawn,                           {.v = brightnessup} },
         { 0, XF86XK_MonBrightnessDown, spawn,                           {.v = brightnessdown} },


         { 0,                            XK_F5,     spawn,               SHCMD("setbg") },

         { MODKEY,                       XK_n,      spawn,               {.v = slockcmd } },


	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
 

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

