#ifdef __cplusplus
extern "C" {
#endif

#ifndef DARWIN
#define _POSIX_C_SOURCE 200809L
#endif
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h> /* for offsetof() macro */
#include <string.h>
#include <math.h>
#include "uemf.h"
#include "emf2svg.h"
#include "emf2svg_private.h"
#include "emf2svg_print.h"
#include "pmf2svg.h"
#include "pmf2svg_print.h"

void U_EMREXCLUDECLIPRECT_draw(const char *contents, FILE *out,
                               drawingStates *states) {
    FLAG_IGNORED;
    if (states->verbose) {
        U_EMREXCLUDECLIPRECT_print(contents, states);
    }
    PU_EMRELLIPSE pEmr = (PU_EMRELLIPSE)(contents);
    U_RECTL rect = pEmr->rclBox;
    U_POINT pt;
    PATH *new_path = NULL;

    add_new_seg(&new_path, SEG_MOVE);
    pt.x = rect.left;
    pt.y = rect.top;
    new_path->section.points[0] = point_s(states, pt);

    add_new_seg(&new_path, SEG_LINE);
    pt.x = rect.right;
    pt.y = rect.top;
    new_path->section.points[0] = point_s(states, pt);

    add_new_seg(&new_path, SEG_LINE);
    pt.x = rect.right;
    pt.y = rect.bottom;
    new_path->section.points[0] = point_s(states, pt);

    add_new_seg(&new_path, SEG_LINE);
    pt.x = rect.left;
    pt.y = rect.bottom;
    new_path->section.points[0] = point_s(states, pt);

    add_new_seg(&new_path, SEG_LINE);
    pt.x = rect.left;
    pt.y = rect.top;
    new_path->section.points[0] = point_s(states, pt);

    add_new_seg(&new_path, SEG_END);

    clip_rgn_mix(states, new_path, U_RGN_DIFF);
    free_path(&new_path);
}
void U_EMREXTSELECTCLIPRGN_draw(const char *contents, FILE *out,
                                drawingStates *states) {
    FLAG_IGNORED;
    if (states->verbose) {
        U_EMREXTSELECTCLIPRGN_print(contents, states);
    }
    // PU_EMREXTSELECTCLIPRGN pEmr = (PU_EMREXTSELECTCLIPRGN) (contents);
}
void U_EMRINTERSECTCLIPRECT_draw(const char *contents, FILE *out,
                                 drawingStates *states) {
    FLAG_IGNORED;
    if (states->verbose) {
        U_EMRINTERSECTCLIPRECT_print(contents, states);
    }
    PU_EMRELLIPSE pEmr = (PU_EMRELLIPSE)(contents);
    U_RECTL rect = pEmr->rclBox;
    U_POINT pt;
    PATH *new_path = NULL;

    add_new_seg(&new_path, SEG_MOVE);
    pt.x = rect.left;
    pt.y = rect.top;
    new_path->section.points[0] = point_s(states, pt);

    add_new_seg(&new_path, SEG_LINE);
    pt.x = rect.right;
    pt.y = rect.top;
    new_path->section.points[0] = point_s(states, pt);

    add_new_seg(&new_path, SEG_LINE);
    pt.x = rect.right;
    pt.y = rect.bottom;
    new_path->section.points[0] = point_s(states, pt);

    add_new_seg(&new_path, SEG_LINE);
    pt.x = rect.left;
    pt.y = rect.bottom;
    new_path->section.points[0] = point_s(states, pt);

    add_new_seg(&new_path, SEG_LINE);
    pt.x = rect.left;
    pt.y = rect.top;
    new_path->section.points[0] = point_s(states, pt);

    add_new_seg(&new_path, SEG_END);

    clip_rgn_mix(states, new_path, U_RGN_AND);
    free_path(&new_path);
}
void U_EMROFFSETCLIPRGN_draw(const char *contents, FILE *out,
                             drawingStates *states) {
    FLAG_IGNORED;
    if (states->verbose) {
        U_EMROFFSETCLIPRGN_print(contents, states);
    }
    PU_EMROFFSETCLIPRGN pEmr = (PU_EMROFFSETCLIPRGN)(contents);
    offset_path(states->currentDeviceContext.clipRGN,
                point_s(states, pEmr->ptlOffset));
}
void U_EMRSELECTCLIPPATH_draw(const char *contents, FILE *out,
                              drawingStates *states) {
    FLAG_IGNORED;
    if (states->verbose) {
        U_EMRSELECTCLIPPATH_print(contents, states);
    }
    PU_EMRSELECTCLIPPATH pEmr = (PU_EMRSELECTCLIPPATH)(contents);
    clip_rgn_mix(states, states->currentPath, pEmr->iMode);
}

#ifdef __cplusplus
}
#endif
/* vim:set shiftwidth=2 softtabstop=2 expandtab: */
