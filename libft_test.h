#ifndef LIBFT_TEST_H
#define LIBFT_TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>
#include <unistd.h>
#include <stdint.h>

#include "avail.h"

#define MAX_FAILURES 64
#define MAX_FAIL_MSG 256

static int g_tests_run      = 0;
static int g_tests_passed   = 0;
static int g_tests_failed   = 0;
static int g_suites_failed  = 0;
static int g_suites_skipped = 0;
static int g_total_suites   = 0;
static int g_verbose        = 0;

static int         g_suite_index        = 0;
static int         g_suite_fails_before = 0;
static const char *g_suite_name         = NULL;
static char        g_fail_msgs[MAX_FAILURES][MAX_FAIL_MSG];
static int         g_fail_msg_count     = 0;

#define RED    "\033[0;31m"
#define GREEN  "\033[0;32m"
#define YELLOW "\033[0;33m"
#define CYAN   "\033[0;36m"
#define BOLD   "\033[1m"
#define DIM    "\033[2m"
#define RESET  "\033[0m"

#define PRINT_LOGO() do { \
	printf(CYAN \
          "/* *************************************************************************** */\n" \
          "/*                                                                             */\n" \
          "/*                                                         :::      ::::::::   */\n" \
          "/*                                                       :+:      :+:    :+:   */\n" \
          "/*  The mystery of life isn't a problem to solve,      +:+ +:+         +:+     */\n" \
          "/*  but a reality to experience.                     +#+  +:+       +#+        */\n" \
          "/*                                                 +#+#+#+#+#+   +#+           */\n" \
          "/*                                                      #+#    #+#             */\n" \
          "/*                                                     ###   ####.fr           */\n" \
          "/*                                                                             */\n" \
          "/* *************************************************************************** */\n" \
	RESET "\n"); \
} while (0)

#define TEST_START(name) do { \
	g_suite_index++; \
	g_suite_fails_before = g_tests_failed; \
	g_suite_name = name; \
	g_fail_msg_count = 0; \
} while (0)

#define TEST_SKIP(name) do { \
	g_suite_index++; \
	g_suites_skipped++; \
	printf(YELLOW DIM " [%2d/%d] SKIP " RESET DIM " %s" RESET "\n", \
		g_suite_index, g_total_suites, name); \
} while (0)

#define TEST_END() do { \
	if (g_tests_failed > g_suite_fails_before) { \
		g_suites_failed++; \
		printf(RED BOLD " [%2d/%d] FAIL " RESET " %s\n", \
			g_suite_index, g_total_suites, g_suite_name); \
		for (int _i = 0; _i < g_fail_msg_count; _i++) \
			printf("                %s\n", g_fail_msgs[_i]); \
	} else { \
		printf(GREEN BOLD " [%2d/%d]  OK  " RESET " %s\n", \
			g_suite_index, g_total_suites, g_suite_name); \
	} \
} while (0)

#define RECORD_FAIL(...) do { \
	if (g_fail_msg_count < MAX_FAILURES) \
		snprintf(g_fail_msgs[g_fail_msg_count++], MAX_FAIL_MSG, __VA_ARGS__); \
} while (0)

#define ASSERT_EQ(tag, got, expected) do { \
	int _got = (int)(got); int _exp = (int)(expected); \
	g_tests_run++; \
	if (_got == _exp) { \
		g_tests_passed++; \
		if (g_verbose) \
			printf(GREEN "   OK  " RESET " %s => %d\n", tag, _got); \
	} else { \
		g_tests_failed++; \
		RECORD_FAIL("%s: got %d, expected %d", tag, _got, _exp); \
		if (g_verbose) \
			printf(RED "  FAIL " RESET " %s: got %d, expected %d\n", \
				tag, _got, _exp); \
	} \
} while (0)

#define ASSERT_EQ_SIZE(tag, got, expected) do { \
	size_t _got = (size_t)(got); size_t _exp = (size_t)(expected); \
	g_tests_run++; \
	if (_got == _exp) { \
		g_tests_passed++; \
		if (g_verbose) \
			printf(GREEN "   OK  " RESET " %s => %zu\n", tag, _got); \
	} else { \
		g_tests_failed++; \
		RECORD_FAIL("%s: got %zu, expected %zu", tag, _got, _exp); \
		if (g_verbose) \
			printf(RED "  FAIL " RESET " %s: got %zu, expected %zu\n", \
				tag, _got, _exp); \
	} \
} while (0)

#define ASSERT_EQ_PTR(tag, got, expected) do { \
	const void *_got = (const void *)(got); \
	const void *_exp = (const void *)(expected); \
	g_tests_run++; \
	if (_got == _exp) { \
		g_tests_passed++; \
		if (g_verbose) \
			printf(GREEN "   OK  " RESET " %s => %p\n", tag, _got); \
	} else { \
		g_tests_failed++; \
		RECORD_FAIL("%s: got %p, expected %p", tag, _got, _exp); \
		if (g_verbose) \
			printf(RED "  FAIL " RESET " %s: got %p, expected %p\n", \
				tag, _got, _exp); \
	} \
} while (0)

#define ASSERT_EQ_STR(tag, got, expected) do { \
	const char *_got = (got); const char *_exp = (expected); \
	g_tests_run++; \
	if (strcmp(_got, _exp) == 0) { \
		g_tests_passed++; \
		if (g_verbose) \
			printf(GREEN "   OK  " RESET " %s => \"%s\"\n", tag, _got); \
	} else { \
		g_tests_failed++; \
		RECORD_FAIL("%s: got \"%s\", expected \"%s\"", tag, _got, _exp); \
		if (g_verbose) \
			printf(RED "  FAIL " RESET " %s: got \"%s\", expected \"%s\"\n", \
				tag, _got, _exp); \
	} \
} while (0)

#define ASSERT_MEM_EQ(tag, got, expected, n) do { \
	g_tests_run++; \
	if (memcmp((got), (expected), (n)) == 0) { \
		g_tests_passed++; \
		if (g_verbose) \
			printf(GREEN "   OK  " RESET " %s\n", tag); \
	} else { \
		g_tests_failed++; \
		RECORD_FAIL("%s: memory differs", tag); \
		if (g_verbose) \
			printf(RED "  FAIL " RESET " %s: memory differs\n", tag); \
	} \
} while (0)

#define ASSERT_SIGN_EQ(tag, got, expected) do { \
	g_tests_run++; \
	int _g = (got); int _e = (expected); \
	if ((_g > 0 && _e > 0) || (_g < 0 && _e < 0) || (_g == 0 && _e == 0)) { \
		g_tests_passed++; \
		if (g_verbose) \
			printf(GREEN "   OK  " RESET " %s => %d\n", tag, _g); \
	} else { \
		g_tests_failed++; \
		RECORD_FAIL("%s: got %d, expected %d (sign mismatch)", tag, _g, _e); \
		if (g_verbose) \
			printf(RED "  FAIL " RESET " %s: got %d, expected %d (sign mismatch)\n", \
				tag, _g, _e); \
	} \
} while (0)

extern void	*__real_malloc(size_t size);
extern void	__real_free(void *ptr);

#define TRACK_MAX 256

static int	g_malloc_fail_after = -1;
static int	g_malloc_call_count = 0;
static int	g_track_enabled = 0;
static void	*g_tracked_allocs[TRACK_MAX];
static int	g_tracked_count = 0;
static int	g_freed_count = 0;

static inline void	malloc_will_fail_after(int n)
{
	g_malloc_fail_after = n;
	g_malloc_call_count = 0;
}

static inline void	malloc_reset(void)
{
	g_malloc_fail_after = -1;
	g_malloc_call_count = 0;
}

static inline void	track_allocs_start(void)
{
	g_track_enabled = 1;
	g_tracked_count = 0;
	g_freed_count = 0;
}

static inline void	track_allocs_stop(void)
{
	g_track_enabled = 0;
}

static inline int	track_leaks(void)
{
	return (g_tracked_count - g_freed_count);
}

#define TEST_SUMMARY() do { \
	printf("\n"); \
	if (g_tests_failed == 0 && g_suites_skipped == 0) \
		printf(GREEN BOLD "All %d tests passed (%d/%d suites)" \
			RESET "\n", g_tests_run, g_total_suites, g_total_suites); \
	else if (g_tests_failed == 0) \
		printf(GREEN BOLD "All %d tests passed (%d/%d suites, %d skipped)" \
			RESET "\n", g_tests_run, \
			g_total_suites - g_suites_skipped, g_total_suites, \
			g_suites_skipped); \
	else \
		printf(RED BOLD "%d/%d tests failed (%d/%d suites failed" \
			RESET, \
			g_tests_failed, g_tests_run, \
			g_suites_failed, g_total_suites); \
	if (g_tests_failed > 0 && g_suites_skipped > 0) \
		printf(RED BOLD ", %d skipped" RESET, g_suites_skipped); \
	if (g_tests_failed > 0) \
		printf(RED BOLD ")" RESET "\n"); \
	return (g_tests_failed > 0); \
} while (0)

#endif
