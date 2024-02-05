/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>
/* appearance */
static const unsigned int borderpx = 3; /* border pixel of windows */
static const unsigned int gappx = 0;    /* border pixel of windows */
static const unsigned int snap = 32;
static const unsigned int systraypinning =
    0; /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor
          X */
static const unsigned int systrayonleft =
    0; /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2; /* systray spacing */
static const int systraypinningfailfirst =
    1; /* 1: if pinning fails, display systray on the first monitor, False:
          display systray on the last monitor*/
       /* snap pixel */
static const char panel[][20] = {"xfce4-panel",
                                 "Xfce4-panel"}; /* name & cls of panel win */
static const int showbar = 1;                    /* 0 means no bar */
static const int topbar = 1;
static const int showsystray = 1;
/* 0 means no systray */ /* 0 means bottom bar */
static const char *fonts[] = {"SF Mono:size=14",
                              "Noto Color Emoji:size=14",
                              "CoconNextArabic-Light:size=14"};
static const char dmenufont[] = "SF Mono:size=14";
static const char col1[] = "#ffffff";
static const char col2[] = "#ffffff";
static const char col3[] = "#ffffff";
static const char col4[] = "#ffffff";
static const char col5[] = "#ffffff";
static const char col6[] = "#ffffff";
static const char col_gray1[] = "#1E1D2D";
static const char col_gray2[] = "#585767";
static const char col_gray3[] = "#585767";
static const char col_gray4[] = "#96CDFB";
static const char col_cyan[] = "#282737";
static const char col_black[] = "#1E1D2D";
static const char col_blue[] = "#96CDFB"; // focused window border
static const char col_green[] = "#ABE9B3";
static const char col_red[] = "#F28FAD";
static const char col_orange[] = "#F8BD96";
static const char col_yellow[] = "#FAE3B0";
static const char col_teal[] = "#94E2D5";
static const char col_blu[] = "#008080";
static const char col_borderbar[] = "#1E1D2D"; // inner border

enum {
  SchemeNorm,
  SchemeCol1,
  SchemeCol2,
  SchemeCol3,
  SchemeCol4,
  SchemeCol5,
  SchemeCol6,
  SchemeSel
};

static const char *colors[][3] = {
    /*               fg             bg          border   */
    [SchemeNorm] = {col_gray3, col_black, col_gray1},
    [SchemeCol1] = {col1, col_gray1, col_gray2},
    [SchemeCol2] = {col2, col_gray1, col_gray2},
    [SchemeCol3] = {col3, col_gray1, col_gray2},
    [SchemeCol4] = {col4, col_gray1, col_gray2},
    [SchemeCol5] = {col5, col_gray1, col_gray2},
    [SchemeCol6] = {col6, col_gray1, col_gray2},
    [SchemeSel] = {col_teal, col_black, col_teal},
};

typedef struct {
  const char *name;
  const void *cmd;
} Sp;

const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL};
const char *spcmd2[] = {"st",     "-n", "spfm",   "-g",
                        "144x41", "-e", "ranger", NULL};
const char *spcmd3[] = {"keepassxc", NULL};
static Sp scratchpads[] = {
    /* name          cmd  */
    {"spterm", spcmd1},
    {"spranger", spcmd2},
    {"keepassxc", spcmd3},
};

/* tagging */
static const char *tags[] = {"",  "󰯊", "󰅨", "󰜬",    "",
                             "󰌶", "󰮤", "󱍑", "󰒱"};
// "\uf19d",

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance      title           tags mask isfloating monitor */
    {"copyq", NULL, NULL, 0, 1, -1},
    {"Slack", NULL, NULL, 1 << 8, 0, -1},
    {NULL, "spterm", NULL, SPTAG(0), 1, -1},
    {NULL, "spfm", NULL, SPTAG(1), 1, -1},
    {NULL, "keepassxc", NULL, SPTAG(2), 0, -1},
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
static const char *dmenucmd[] = {"dmenu_run", "-fn", dmenufont, "-nb",
                                 col_gray1,   "-nf", col_gray3, "-sb",
                                 col_cyan,    "-sf", col_gray4, NULL};
static const char *termcmd[] = {"st", NULL};

static const Key keys[] = {
    /* modifier                     key        function        argument */
    {MODKEY, XK_d, spawn, {.v = dmenucmd}},
    {MODKEY, XK_p, spawn, {.v = dmenucmd}},
    {MODKEY, XK_Return, spawn, {.v = termcmd}},
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY, XK_i, incnmaster, {.i = +1}},
    {MODKEY, XK_o, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY | ShiftMask, XK_Return, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY | ShiftMask, XK_q, killclient, {0}},
    {MODKEY, XK_F2, view_adjacent, {.i = +1}},
    {MODKEY, XK_F1, view_adjacent, {.i = -1}},
    {MODKEY | ShiftMask, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY | ShiftMask, XK_y, setlayout, {.v = &layouts[1]}},
    {MODKEY, XK_f, fullscreen, {0}},
    {MODKEY, XK_space, setlayout, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    // SCRATCH PAD
    {MODKEY, XK_y, togglescratch, {.ui = 0}},
    {MODKEY, XK_u, togglescratch, {.ui = 1}},
    {MODKEY, XK_x, togglescratch, {.ui = 2}},
    {MODKEY | ShiftMask, XK_a, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    // FOCUS MONITOR
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    /// TAG MONITOR
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8){MODKEY | ShiftMask, XK_c, quit, {0}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function argument */
    // { ClkTagBar,            MODKEY,         Button1,        tag, {0} }, {
    // ClkTagBar,            MODKEY,         Button3,        toggletag,      {0}
    // }, { ClkWinTitle,          0,              Button2,        zoom, {0} },
    // { ClkStatusText,        0,              Button2,        spawn, {.v =
    // termcmd } },
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
