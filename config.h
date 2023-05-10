/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=12" };
static const char dmenufont[]       = "monospace:size=12";

#define NorFG "#FFFFFF"
#define NorBG "#111222"
#define NorBo "#333333"
#define SelFG "#FFFFFF"
#define SelBG "#28284D"
#define SelBo "#666666"

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { NorFG, NorBG, NorBo },
	[SchemeSel]  = { SelFG, SelBG, SelBo },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "<><",      NULL },    /* no layout function means floating behavior */
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
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/bash", "-c", cmd, NULL } }

/* commands */
#define DMENU_ARGS "-m", "0", "-fn", dmenufont, "-nb", NorBG, "-nf", NorFG, "-sb", SelBG, "-sf", SelFG
static const char *dmenucmd[] = { "dmenu_run", DMENU_ARGS, NULL };
static const char *appmenucmd[] = { "appmenu", "$HOME/.config/appmenu/", DMENU_ARGS, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *dunstclose[] = { "dunstctl", "close-all", NULL };
static const char *dunsthist[] = { "dunstctl", "history-pop", NULL };

static const Key keys[] = {
	/* modifier                     key        	function        	argument */
	{ MODKEY|ShiftMask,             XK_r,      	spawn,			{.v = dmenucmd } },
	{ MODKEY,                       XK_r,      	spawn,			{.v = appmenucmd } },
	{ MODKEY,                       XK_Return, 	spawn,			{.v = termcmd } },
	{ MODKEY,                       XK_b,      	togglebar,		{0} },
	{ MODKEY|ShiftMask,             XK_j,      	rotatestack,		{.i = +1 } },
        { MODKEY|ShiftMask,             XK_k,      	rotatestack,		{.i = -1 } },
	{ MODKEY,                       XK_j,      	focusstack,		{.i = +1 } },
	{ MODKEY,                       XK_k,      	focusstack,		{.i = -1 } },
	{ MODKEY,                       XK_i,      	incnmaster,		{.i = +1 } },
	{ MODKEY,                       XK_d,      	incnmaster,		{.i = -1 } },
	{ MODKEY,                       XK_h,      	setmfact,		{.f = -0.05} },
	{ MODKEY,                       XK_l,      	setmfact,		{.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, 	zoom,			{0} },
	{ MODKEY,	                XK_Tab,    	shiftviewclients,	{ .i = +1 } },
	{ MODKEY|ShiftMask,             XK_Tab,    	shiftviewclients,	{ .i = -1 }},
	{ MODKEY|ControlMask,		XK_Tab,    	view,			{0} },
	{ MODKEY,                       XK_c,      	killclient,		{0} },
	{ MODKEY,                       XK_t,      	setlayout,		{.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      	setlayout,		{.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      	setlayout,		{.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_space,  	togglefloating,		{0} },
	{ MODKEY,                       XK_eacute,     	view,			{.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_eacute,     	tag,			{.ui = ~0 } },
	{ MODKEY,                       XK_comma,  	focusmon,		{.i = -1 } },
	{ MODKEY,                       XK_period, 	focusmon,		{.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  	tagmon,			{.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, 	tagmon,			{.i = +1 } },
	{ MODKEY|ShiftMask,             XK_q,		quit,			{0} },
	TAGKEYS(                        XK_plus,	0)
	TAGKEYS(                        XK_ecaron,	1)
	TAGKEYS(                        XK_scaron,	2)
	TAGKEYS(                        XK_ccaron,	3)
	TAGKEYS(                        XK_rcaron,	4)
	TAGKEYS(                        XK_zcaron,	5)
	TAGKEYS(                        XK_yacute,	6)
	TAGKEYS(                        XK_aacute,	7)
	TAGKEYS(                        XK_iacute,	8)
	{ MODKEY,			XK_Escape,	spawn,			{.v = dunstclose } },
	{ MODKEY|ShiftMask,		XK_Escape,	spawn,			{.v = dunsthist } },
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

