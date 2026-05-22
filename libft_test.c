#include "libft_test.h"

void	*__wrap_malloc(size_t size)
{
	void	*ptr;

	if (g_malloc_fail_after >= 0)
	{
		g_malloc_call_count++;
		if (g_malloc_call_count > g_malloc_fail_after)
			return (NULL);
	}
	ptr = __real_malloc(size);
	if (ptr && g_track_enabled && g_tracked_count < TRACK_MAX)
		g_tracked_allocs[g_tracked_count++] = ptr;
	return (ptr);
}

void	__wrap_free(void *ptr)
{
	if (ptr && g_track_enabled)
	{
		for (int i = 0; i < g_tracked_count; i++)
		{
			if (g_tracked_allocs[i] == ptr)
			{
				g_freed_count++;
				g_tracked_allocs[i] = NULL;
				break ;
			}
		}
	}
	__real_free(ptr);
}

int ft_isalpha(int c);

static void test_isalpha(void) {
  TEST_START("ft_isalpha");
  for (int c = -1; c <= 200; c++) {
    char tag[32];
    sprintf(tag, "ft_isalpha(%d)", c);
    ASSERT_EQ(tag, !!ft_isalpha(c), !!isalpha(c));
  }
  TEST_END();
}

int ft_isdigit(int c);

static void test_isdigit(void) {
  TEST_START("ft_isdigit");
  for (int c = -1; c <= 200; c++) {
    char tag[32];
    sprintf(tag, "ft_isdigit(%d)", c);
    ASSERT_EQ(tag, !!ft_isdigit(c), !!isdigit(c));
  }
  TEST_END();
}

int ft_isalnum(int c);

static void test_isalnum(void) {
  TEST_START("ft_isalnum");
  for (int c = -1; c <= 200; c++) {
    char tag[32];
    sprintf(tag, "ft_isalnum(%d)", c);
    ASSERT_EQ(tag, !!ft_isalnum(c), !!isalnum(c));
  }
  TEST_END();
}

int ft_isascii(int c);

static void test_isascii(void) {
  TEST_START("ft_isascii");
  for (int c = -1; c <= 200; c++) {
    char tag[32];
    sprintf(tag, "ft_isascii(%d)", c);
    ASSERT_EQ(tag, !!ft_isascii(c), !!isascii(c));
  }
  TEST_END();
}

int ft_isprint(int c);

static void test_isprint(void) {
  TEST_START("ft_isprint");
  for (int c = -1; c <= 200; c++) {
    char tag[32];
    sprintf(tag, "ft_isprint(%d)", c);
    ASSERT_EQ(tag, !!ft_isprint(c), !!isprint(c));
  }
  TEST_END();
}

int ft_toupper(int c);

static void test_toupper(void) {
  TEST_START("ft_toupper");
  for (int c = 0; c <= 127; c++) {
    char tag[32];
    sprintf(tag, "ft_toupper(%d)", c);
    ASSERT_EQ(tag, ft_toupper(c), toupper(c));
  }
  TEST_END();
}

int ft_tolower(int c);

static void test_tolower(void) {
  TEST_START("ft_tolower");
  for (int c = 0; c <= 127; c++) {
    char tag[32];
    sprintf(tag, "ft_tolower(%d)", c);
    ASSERT_EQ(tag, ft_tolower(c), tolower(c));
  }
  TEST_END();
}

size_t ft_strlen(const char *s);

static void test_strlen(void) {
  TEST_START("ft_strlen");
  ASSERT_EQ_SIZE("ft_strlen(\"\")", ft_strlen(""), strlen(""));
  ASSERT_EQ_SIZE("ft_strlen(\"hello\")", ft_strlen("hello"), strlen("hello"));
  ASSERT_EQ_SIZE("ft_strlen(\"a\")", ft_strlen("a"), strlen("a"));
  ASSERT_EQ_SIZE("ft_strlen(\"abcdefghijklmnopqrstuvwxyz\")", ft_strlen("abcdefghijklmnopqrstuvwxyz"), strlen("abcdefghijklmnopqrstuvwxyz"));
  TEST_END();
}

void *ft_memset(void *s, int c, size_t n);

static void test_memset(void) {
  TEST_START("ft_memset");
  
  char buf1[20];
  char buf2[20];

  ft_memset(buf1, 'A', 10);
  memset(buf2, 'A', 10);
  ASSERT_MEM_EQ("ft_memset(buf, 'A', 10)", buf1, buf2, 10);

  ft_memset(buf1, 0, 20);
  memset(buf2, 0, 20);
  ASSERT_MEM_EQ("ft_memset(buf, 0, 20)", buf1, buf2, 20);

  ft_memset(buf1, 255, 5);
  memset(buf2, 255, 5);
  ASSERT_MEM_EQ("ft_memset(buf, 255, 5)", buf1, buf2, 5);

  ft_memset(buf1, 42, 0);
  memset(buf2, 42, (size_t)0);
  ASSERT_MEM_EQ("ft_memset(buf, 42, 0)", buf1, buf2, 0);

  ASSERT_EQ_PTR("ft_memset returns s", ft_memset(buf1, 'A', 5), buf1);

  TEST_END();
}

void ft_bzero(void *s, size_t n);

static void test_bzero(void) {
  TEST_START("ft_bzero");
  
  char buf1[20];
  char buf2[20];

  memset(buf1, 'X', 20);
  memset(buf2, 'X', 20);
  
  ft_bzero(buf1, 10);
  memset(buf2, 0, 10);
  ASSERT_MEM_EQ("ft_bzero(buf, 10)", buf1, buf2, 20);

  // should do nothing
  ft_bzero(buf1, 0);
  ASSERT_MEM_EQ("ft_bzero(buf, 0)", buf1, buf2, 20);

  TEST_END();
}

void *ft_memcpy(void *dest, const void *src, size_t n);

static void test_memcpy(void) {
  TEST_START("ft_memcpy");
  
  char dst1[20];
  char dst2[20];
  char src[] = "hello world!";
  char bin_src[] = {1, 0, 2, 0, 3};

  ft_memcpy(dst1, src, 13);
  memmove(dst2, src, 13);
  ASSERT_MEM_EQ("ft_memcpy(dst, \"hello world!\", 13)", dst1, dst2, 13);

  ft_memcpy(dst1, "", 1);
  memmove(dst2, "", 1);
  ASSERT_MEM_EQ("ft_memcpy(dst, \"\", 1)", dst1, dst2, 1);

  ft_memcpy(dst1, bin_src, 5);
  memmove(dst2, bin_src, 5);
  ASSERT_MEM_EQ("binary with nulls", dst1, dst2, 5);

  ASSERT_EQ_PTR("ft_memcpy returns dest", ft_memcpy(dst1, src, 5), dst1);

  memset(dst1, 'X', 20);
  ft_memcpy(dst1, src, 0);
  ASSERT_EQ("ft_memcpy(dst, src, 0) untouched", dst1[0], 'X');

  TEST_END();
}

void *ft_memmove(void *dest, const void *src, size_t n);

static void test_memmove(void) {
  TEST_START("ft_memmove");
  
  char  buf1[20];
  char  buf2[20];

  memmove(buf1, "hello world", 12);
  memmove(buf2, "hello world", 12);
  ft_memmove(buf1 + 2, buf1, 10);
  memmove(buf2 + 2, buf2, 10);
  ASSERT_MEM_EQ("ft_memmove(buf+2, buf, 10) overlap fwd", buf1, buf2, 12);

  memmove(buf1, "hello world", 12);
  memmove(buf2, "hello world", 12);
  ft_memmove(buf1, buf1 + 2, 10);
  memmove(buf2, buf2 + 2, 10);
  ASSERT_MEM_EQ("ft_memmove(buf, buf+2, 10) overlap bwd", buf1, buf2, 12);

  memmove(buf1, "abcdef", 7);
  memmove(buf2, "abcdef", 7);
  ft_memmove(buf1, buf2, 7);
  ASSERT_MEM_EQ("ft_memmove(dst, src, 7) no overlap", buf1, buf2, 7);

  ASSERT_EQ_PTR("ft_memmove returns dest", ft_memmove(buf1, buf2, 5), buf1);

  memset(buf1, 'X', 20);
  ft_memmove(buf1, buf2, 0);
  ASSERT_EQ("ft_memmove(dst, src, 0) untouched", buf1[0], 'X');

  TEST_END();
}

int ft_memcmp(const void *s1, const void *s2, size_t n);

static void test_memcmp(void) {
  TEST_START("ft_memcmp");
  
  ASSERT_SIGN_EQ("ft_memcmp(\"abc\", \"abc\", 3)", ft_memcmp("abc", "abc", 3), memcmp("abc", "abc", 3));
  ASSERT_SIGN_EQ("ft_memcmp(\"abc\", \"abd\", 3)", ft_memcmp("abc", "abd", 3), memcmp("abc", "abd", 3));
  ASSERT_SIGN_EQ("ft_memcmp(\"abd\", \"abc\", 3)", ft_memcmp("abd", "abc", 3), memcmp("abd", "abc", 3));
  ASSERT_SIGN_EQ("ft_memcmp(\"abc\", \"xyz\", 0)", ft_memcmp("abc", "xyz", 0), memcmp("abc", "xyz", 0));
  ASSERT_SIGN_EQ("ft_memcmp(\"abc\", \"abd\", 2)", ft_memcmp("abc", "abd", 2), memcmp("abc", "abd", 2));

  ASSERT_SIGN_EQ("ft_memcmp(\"\\xff\", \"\\x01\", 1)",
    ft_memcmp("\xff", "\x01", 1), memcmp("\xff", "\x01", 1));
  ASSERT_SIGN_EQ("ft_memcmp(\"\\x01\", \"\\xff\", 1)",
    ft_memcmp("\x01", "\xff", 1), memcmp("\x01", "\xff", 1));
  ASSERT_SIGN_EQ("ft_memcmp(\"abc\", \"abc\", 0)",
    ft_memcmp("abc", "abc", 0), memcmp("abc", "abc", 0));

  TEST_END();
}

void *ft_memchr(const void *s, int c, size_t n);

static void test_memchr(void) {
  TEST_START("ft_memchr");
  
  const char    *s = "hello world";

  ASSERT_EQ_PTR("ft_memchr(s, 'w', 11)", ft_memchr(s, 'w', 11), memchr(s, 'w', 11));
  ASSERT_EQ_PTR("ft_memchr(s, 'h', 11)", ft_memchr(s, 'h', 11), memchr(s, 'h', 11));
  ASSERT_EQ_PTR("ft_memchr(s, 'z', 11)", ft_memchr(s, 'z', 11), memchr(s, 'z', 11));
  ASSERT_EQ_PTR("ft_memchr(s, 'h', 0)", ft_memchr(s, 'h', 0), memchr(s, 'h', 0));
  ASSERT_EQ_PTR("ft_memchr(s, '\\0', 12)", ft_memchr(s, '\0', 12), memchr(s, '\0', 12));

  {
    unsigned char buf[] = {0, 200, 150, 255, 0};
    ASSERT_EQ_PTR("ft_memchr(buf, 200, 5)", ft_memchr(buf, 200, 5), memchr(buf, 200, 5));
    ASSERT_EQ_PTR("ft_memchr(buf, 255, 5)", ft_memchr(buf, 255, 5), memchr(buf, 255, 5));
    ASSERT_EQ_PTR("ft_memchr(buf, 128, 5)", ft_memchr(buf, 128, 5), memchr(buf, 128, 5));
  }

  TEST_END();
}

int ft_strncmp(const char s1[], const char s2[], size_t n);

static void test_strncmp(void) {
  TEST_START("ft_strncmp");
  
  ASSERT_SIGN_EQ("ft_strncmp(\"abc\", \"abc\", 3)", ft_strncmp("abc", "abc", 3), strncmp("abc", "abc", 3));
  ASSERT_SIGN_EQ("ft_strncmp(\"abc\", \"abd\", 3)", ft_strncmp("abc", "abd", 3), strncmp("abc", "abd", 3));
  ASSERT_SIGN_EQ("ft_strncmp(\"abd\", \"abc\", 3)", ft_strncmp("abd", "abc", 3), strncmp("abd", "abc", 3));
  ASSERT_SIGN_EQ("ft_strncmp(\"abc\", \"xyz\", 0)", ft_strncmp("abc", "xyz", 0), strncmp("abc", "xyz", 0));
  ASSERT_SIGN_EQ("ft_strncmp(\"abcdef\", \"abcxyz\", 3)", ft_strncmp("abcdef", "abcxyz", 3), strncmp("abcdef", "abcxyz", 3));
  ASSERT_SIGN_EQ("ft_strncmp(\"abc\", \"abcdef\", 6)", ft_strncmp("abc", "abcdef", 6), strncmp("abc", "abcdef", 6));
  ASSERT_SIGN_EQ("ft_strncmp(\"\", \"\", 1)", ft_strncmp("", "", 1), strncmp("", "", 1));

  ASSERT_SIGN_EQ("ft_strncmp(\"abc\\0x\", \"abc\\0y\", 5)",
    ft_strncmp("abc\0x", "abc\0y", 5), strncmp("abc\0x", "abc\0y", 5));
  ASSERT_SIGN_EQ("ft_strncmp(\"\\200\", \"\\0\", 1)",
    ft_strncmp("\200", "\0", 1), strncmp("\200", "\0", 1));

  TEST_END();
}

int ft_atoi(const char *str);

static void test_atoi(void) {
  TEST_START("ft_atoi");
  
  ASSERT_EQ("ft_atoi(\"42\")", ft_atoi("42"), atoi("42"));
  ASSERT_EQ("ft_atoi(\"-42\")", ft_atoi("-42"), atoi("-42"));
  ASSERT_EQ("ft_atoi(\"0\")", ft_atoi("0"), atoi("0"));
  ASSERT_EQ("ft_atoi(\"  123\")", ft_atoi("  123"), atoi("  123"));
  ASSERT_EQ("ft_atoi(\"\\t456\")", ft_atoi("\t456"), atoi("\t456"));
  ASSERT_EQ("ft_atoi(\"+789\")", ft_atoi("+789"), atoi("+789"));
  ASSERT_EQ("ft_atoi(\"   -42\")", ft_atoi("   -42"), atoi("   -42"));
  ASSERT_EQ("ft_atoi(\"123abc\")", ft_atoi("123abc"), atoi("123abc"));
  ASSERT_EQ("ft_atoi(\"\")", ft_atoi(""), atoi(""));
  ASSERT_EQ("ft_atoi(\"abc\")", ft_atoi("abc"), atoi("abc"));
  ASSERT_EQ("ft_atoi(\"2147483647\")", ft_atoi("2147483647"), atoi("2147483647"));
  ASSERT_EQ("ft_atoi(\"-2147483648\")", ft_atoi("-2147483648"), atoi("-2147483648"));

  ASSERT_EQ("ft_atoi(\"--5\")", ft_atoi("--5"), atoi("--5"));
  ASSERT_EQ("ft_atoi(\"+-5\")", ft_atoi("+-5"), atoi("+-5"));
  ASSERT_EQ("ft_atoi(\"-+5\")", ft_atoi("-+5"), atoi("-+5"));
  ASSERT_EQ("ft_atoi(\"++5\")", ft_atoi("++5"), atoi("++5"));
  ASSERT_EQ("ft_atoi(\"---5\")", ft_atoi("---5"), atoi("---5"));

  ASSERT_EQ("ft_atoi(\"\\n42\")", ft_atoi("\n42"), atoi("\n42"));
  ASSERT_EQ("ft_atoi(\"\\v42\")", ft_atoi("\v42"), atoi("\v42"));
  ASSERT_EQ("ft_atoi(\"\\f42\")", ft_atoi("\f42"), atoi("\f42"));
  ASSERT_EQ("ft_atoi(\"\\r42\")", ft_atoi("\r42"), atoi("\r42"));
  ASSERT_EQ("ft_atoi(\" \\t\\n\\v\\f\\r42\")", ft_atoi(" \t\n\v\f\r42"), atoi(" \t\n\v\f\r42"));

  TEST_END();
}

char *ft_strdup(const char *s);

static void test_strdup(void) {
  TEST_START("ft_strdup");
  
  char  *ft_res;
  char  *libc_res;

  ft_res = ft_strdup("hello");
  libc_res = strdup("hello");
  ASSERT_EQ_STR("ft_strdup(\"hello\")", ft_res, libc_res);
  free(ft_res);
  free(libc_res);

  ft_res = ft_strdup("");
  libc_res = strdup("");
  ASSERT_EQ_STR("ft_strdup(\"\")", ft_res, libc_res);
  free(ft_res);
  free(libc_res);

  ft_res = ft_strdup("a longer test string here");
  libc_res = strdup("a longer test string here");
  ASSERT_EQ_STR("ft_strdup(\"a longer test string here\")", ft_res, libc_res);
  free(ft_res);
  free(libc_res);

  malloc_will_fail_after(0);
  ft_res = ft_strdup("hello");
  malloc_reset();
  ASSERT_EQ_PTR("ft_strdup malloc fail returns NULL", ft_res, NULL);

  TEST_END();
}

void *ft_calloc(size_t n, size_t size);

static void test_calloc(void) {
  TEST_START("ft_calloc");
  
  unsigned char *ft_res;
  unsigned char *libc_res;
  int                           all_zero;

  ft_res = ft_calloc(10, sizeof(int));
  libc_res = calloc(10, sizeof(int));
  ASSERT_MEM_EQ("ft_calloc(10, sizeof(int))", ft_res, libc_res,
                10 * sizeof(int));
  free(ft_res);
  free(libc_res);

  ft_res = ft_calloc(1, 1);
  all_zero = (ft_res[0] == 0);
  ASSERT_EQ("ft_calloc(1, 1) zeroed", all_zero, 1);
  free(ft_res);

  ft_res = ft_calloc(100, 1);
  all_zero = 1;
  for (int i = 0; i < 100; i++)
    if (ft_res[i] != 0)
      all_zero = 0;
  ASSERT_EQ("ft_calloc(100, 1) all zeroed", all_zero, 1);
  free(ft_res);

#pragma GCC diagnostic push
#if defined(__has_warning)
# if __has_warning("-Walloc-size")
#  pragma GCC diagnostic ignored "-Walloc-size"
# endif
#elif defined(__GNUC__) && (__GNUC__ >= 14)
# pragma GCC diagnostic ignored "-Walloc-size"
#endif
  ft_res = ft_calloc(0, 5);
  libc_res = calloc(0, 5);
  ASSERT_EQ("ft_calloc(0, 5) both NULL or both non-NULL",
            (ft_res != NULL), (libc_res != NULL));
  free(ft_res);
  free(libc_res);

  ft_res = ft_calloc(5, 0);
  libc_res = calloc(5, 0);
  ASSERT_EQ("ft_calloc(5, 0) both NULL or both non-NULL",
            (ft_res != NULL), (libc_res != NULL));
  free(ft_res);
  free(libc_res);
#pragma GCC diagnostic pop

  ft_res = ft_calloc(SIZE_MAX, SIZE_MAX);
  ASSERT_EQ_PTR("ft_calloc(SIZE_MAX, SIZE_MAX) overflow returns NULL",
                ft_res, NULL);

  TEST_END();
}

char *ft_strchr(const char *s, int c);

static void test_strchr(void) {
  TEST_START("ft_strchr");
  
  const char    *s = "hello world";

  ASSERT_EQ_PTR("ft_strchr(\"hello world\", 'w')", ft_strchr(s, 'w'), strchr(s, 'w'));
  ASSERT_EQ_PTR("ft_strchr(\"hello world\", 'h')", ft_strchr(s, 'h'), strchr(s, 'h'));
  ASSERT_EQ_PTR("ft_strchr(\"hello world\", 'l')", ft_strchr(s, 'l'), strchr(s, 'l'));
  ASSERT_EQ_PTR("ft_strchr(\"hello world\", 'z')", ft_strchr(s, 'z'), strchr(s, 'z'));
  ASSERT_EQ_PTR("ft_strchr(\"hello world\", '\\0')", ft_strchr(s, '\0'), strchr(s, '\0'));
  ASSERT_EQ_PTR("ft_strchr(\"\", 'a')", ft_strchr("", 'a'), strchr("", 'a'));
  ASSERT_EQ_PTR("ft_strchr(\"\", '\\0')", ft_strchr("", '\0'), strchr("", '\0'));

  ASSERT_EQ_PTR("ft_strchr(\"hello\", 'h' + 256)", ft_strchr("hello", 'h' + 256), strchr("hello", 'h' + 256));
  ASSERT_EQ_PTR("ft_strchr(\"hello\", 1024)", ft_strchr("hello", 1024), strchr("hello", 1024));

  TEST_END();
}

char *ft_strrchr(const char *s, int c);

static void test_strrchr(void) {
  TEST_START("ft_strrchr");
  
  const char    *s = "hello world";

  ASSERT_EQ_PTR("ft_strrchr(\"hello world\", 'l')", ft_strrchr(s, 'l'), strrchr(s, 'l'));
  ASSERT_EQ_PTR("ft_strrchr(\"hello world\", 'o')", ft_strrchr(s, 'o'), strrchr(s, 'o'));
  ASSERT_EQ_PTR("ft_strrchr(\"hello world\", 'h')", ft_strrchr(s, 'h'), strrchr(s, 'h'));
  ASSERT_EQ_PTR("ft_strrchr(\"hello world\", 'z')", ft_strrchr(s, 'z'), strrchr(s, 'z'));
  ASSERT_EQ_PTR("ft_strrchr(\"hello world\", '\\0')", ft_strrchr(s, '\0'), strrchr(s, '\0'));
  ASSERT_EQ_PTR("ft_strrchr(\"\", 'a')", ft_strrchr("", 'a'), strrchr("", 'a'));
  ASSERT_EQ_PTR("ft_strrchr(\"a\", 'a')", ft_strrchr("a", 'a'), strrchr("a", 'a'));

  ASSERT_EQ_PTR("ft_strrchr(\"hello\", 'h' + 256)", ft_strrchr("hello", 'h' + 256), strrchr("hello", 'h' + 256));
  ASSERT_EQ_PTR("ft_strrchr(\"hello\", 'o' + 256)", ft_strrchr("hello", 'o' + 256), strrchr("hello", 'o' + 256));
  ASSERT_EQ_PTR("ft_strrchr(\"hello\", 1024)", ft_strrchr("hello", 1024), strrchr("hello", 1024));

  TEST_END();
}

size_t ft_strlcpy(char *dst, const char *src, size_t size);

static void test_strlcpy(void) {
  TEST_START("ft_strlcpy");
  
  char  buf[20];
  size_t        ret;

  memset(buf, 'X', 20);
  ret = ft_strlcpy(buf, "hello", 20);
  ASSERT_EQ_SIZE("ft_strlcpy(buf, \"hello\", 20) ret", ret, 5);
  ASSERT_EQ_STR("ft_strlcpy(buf, \"hello\", 20) buf", buf, "hello");

  memset(buf, 'X', 20);
  ret = ft_strlcpy(buf, "hello", 3);
  ASSERT_EQ_SIZE("ft_strlcpy(buf, \"hello\", 3) ret", ret, 5);
  ASSERT_EQ("ft_strlcpy(buf, \"hello\", 3) buf[2]", buf[2], '\0');
  ASSERT_EQ("ft_strlcpy(buf, \"hello\", 3) buf[0]", buf[0], 'h');
  ASSERT_EQ("ft_strlcpy(buf, \"hello\", 3) buf[1]", buf[1], 'e');

  memset(buf, 'X', 20);
  ret = ft_strlcpy(buf, "hello", 1);
  ASSERT_EQ_SIZE("ft_strlcpy(buf, \"hello\", 1) ret", ret, 5);
  ASSERT_EQ("ft_strlcpy(buf, \"hello\", 1) buf[0]", buf[0], '\0');

  memset(buf, 'X', 20);
  ret = ft_strlcpy(buf, "hello", 0);
  ASSERT_EQ_SIZE("ft_strlcpy(buf, \"hello\", 0) ret", ret, 5);
  ASSERT_EQ("ft_strlcpy(buf, \"hello\", 0) untouched", buf[0], 'X');

  memset(buf, 'X', 20);
  ret = ft_strlcpy(buf, "", 20);
  ASSERT_EQ_SIZE("ft_strlcpy(buf, \"\", 20) ret", ret, 0);
  ASSERT_EQ("ft_strlcpy(buf, \"\", 20) buf[0]", buf[0], '\0');

  TEST_END();
}

size_t ft_strlcat(char *dst, const char *src, size_t size);

static void test_strlcat(void) {
  TEST_START("ft_strlcat");
  
  char  buf[20];
  size_t        ret;

  memset(buf, 0, 20);
  memmove(buf, "hello\0", 6);
  ret = ft_strlcat(buf, " world", 20);
  ASSERT_EQ_SIZE("ft_strlcat(\"hello\", \" world\", 20) ret", ret, 11);
  ASSERT_EQ_STR("ft_strlcat(\"hello\", \" world\", 20) buf", buf, "hello world");

  memset(buf, 0, 20);
  memmove(buf, "hello\0", 6);
  ret = ft_strlcat(buf, " world", 8);
  ASSERT_EQ_SIZE("ft_strlcat(\"hello\", \" world\", 8) ret", ret, 11);
  ASSERT_EQ("ft_strlcat(\"hello\", \" world\", 8) buf[7]", buf[7], '\0');
  ASSERT_EQ_STR("ft_strlcat(\"hello\", \" world\", 8) buf", buf, "hello w");

  memset(buf, 0, 20);
  memmove(buf, "hello\0", 6);
  ret = ft_strlcat(buf, " world", 5);
  ASSERT_EQ_SIZE("ft_strlcat(\"hello\", \" world\", 5) ret", ret, 11);
  ASSERT_EQ_STR("ft_strlcat(\"hello\", \" world\", 5) buf", buf, "hello");

  memset(buf, 0, 20);
  memmove(buf, "hello\0", 6);
  ret = ft_strlcat(buf, "", 20);
  ASSERT_EQ_SIZE("ft_strlcat(\"hello\", \"\", 20) ret", ret, 5);
  ASSERT_EQ_STR("ft_strlcat(\"hello\", \"\", 20) buf", buf, "hello");

  memset(buf, 0, 20);
  buf[0] = '\0';
  ret = ft_strlcat(buf, "hello", 20);
  ASSERT_EQ_SIZE("ft_strlcat(\"\", \"hello\", 20) ret", ret, 5);
  ASSERT_EQ_STR("ft_strlcat(\"\", \"hello\", 20) buf", buf, "hello");

  memset(buf, 0, 20);
  memmove(buf, "hello\0", 6);
  ret = ft_strlcat(buf, " world", 0);
  ASSERT_EQ_SIZE("ft_strlcat(\"hello\", \" world\", 0) ret", ret, 6);

  memset(buf, 0, 20);
  memmove(buf, "hello\0", 6);
  ret = ft_strlcat(buf, " world", 3);
  ASSERT_EQ_SIZE("ft_strlcat(\"hello\", \" world\", 3) ret", ret, 9);
  ASSERT_EQ_STR("ft_strlcat(\"hello\", \" world\", 3) buf unchanged", buf, "hello");

  TEST_END();
}

char *ft_strnstr(const char *big, const char *little, size_t len);

static void test_strnstr(void) {
  TEST_START("ft_strnstr");

  const char    *big = "hello world";

  ASSERT_EQ_PTR("ft_strnstr(\"hello world\", \"world\", 11)", ft_strnstr(big, "world", 11), big + 6);
  ASSERT_EQ_PTR("ft_strnstr(\"hello world\", \"hello\", 11)", ft_strnstr(big, "hello", 11), big);
  ASSERT_EQ_PTR("ft_strnstr(\"hello world\", \"world\", 8)", ft_strnstr(big, "world", 8), NULL);
  ASSERT_EQ_PTR("ft_strnstr(\"hello world\", \"xyz\", 11)", ft_strnstr(big, "xyz", 11), NULL);
  ASSERT_EQ_PTR("ft_strnstr(\"hello world\", \"\", 11)", ft_strnstr(big, "", 11), big);
  ASSERT_EQ_PTR("ft_strnstr(\"hello world\", \"hello\", 0)", ft_strnstr(big, "hello", 0), NULL);
  
  const char *s1 = "abc";
  ASSERT_EQ_PTR("ft_strnstr(\"abc\", \"abc\", 3)", ft_strnstr(s1, "abc", 3), s1);
  
  const char *s2 = "abcabd";
  ASSERT_EQ_PTR("ft_strnstr(\"abcabd\", \"abd\", 6)", ft_strnstr(s2, "abd", 6), s2 + 3);

  const char *s3 = "hello";
  ASSERT_EQ_PTR("ft_strnstr(\"hello\", \"llo\", 5) exact boundary",
    ft_strnstr(s3, "llo", 5), s3 + 2);
  ASSERT_EQ_PTR("ft_strnstr(\"hello\", \"llo\", 4) one short",
    ft_strnstr(s3, "llo", 4), NULL);
  ASSERT_EQ_PTR("ft_strnstr(\"\", \"\", 0) both empty",
    ft_strnstr("", "", 0), (char *)"");

  TEST_END();
}

char *ft_substr(char const *s, unsigned int start, size_t len);

static void test_substr(void) {
  TEST_START("ft_substr");
  
  char  *res;

  res = ft_substr("hello world", 6, 5);
  ASSERT_EQ_STR("ft_substr(\"hello world\", 6, 5)", res, "world");
  free(res);

  res = ft_substr("hello", 0, 5);
  ASSERT_EQ_STR("ft_substr(\"hello\", 0, 5)", res, "hello");
  free(res);

  res = ft_substr("hello", 0, 10);
  ASSERT_EQ_STR("ft_substr(\"hello\", 0, 10)", res, "hello");
  free(res);

  res = ft_substr("hello", 1, 3);
  ASSERT_EQ_STR("ft_substr(\"hello\", 1, 3)", res, "ell");
  free(res);

  res = ft_substr("hello", 5, 5);
  ASSERT_EQ_STR("ft_substr(\"hello\", 5, 5)", res, "");
  free(res);

  res = ft_substr("hello", 10, 5);
  ASSERT_EQ_STR("ft_substr(\"hello\", 10, 5)", res, "");
  free(res);

  res = ft_substr("hello", 0, 0);
  ASSERT_EQ_STR("ft_substr(\"hello\", 0, 0)", res, "");
  free(res);

  res = ft_substr("", 0, 5);
  ASSERT_EQ_STR("ft_substr(\"\", 0, 5)", res, "");
  free(res);

  res = ft_substr("a", 0, 1);
  ASSERT_EQ_STR("ft_substr(\"a\", 0, 1)", res, "a");
  free(res);

  res = ft_substr("hello", 4294967295U, 5);
  ASSERT_EQ_STR("ft_substr(\"hello\", UINT_MAX, 5)", res, "");
  free(res);

  res = ft_substr("hello", 2, 0);
  ASSERT_EQ_STR("ft_substr(\"hello\", 2, 0)", res, "");
  free(res);

  res = ft_substr("hello", 4, 100);
  ASSERT_EQ_STR("ft_substr(\"hello\", 4, 100)", res, "o");
  free(res);

  malloc_will_fail_after(0);
  res = ft_substr("hello", 0, 5);
  malloc_reset();
  ASSERT_EQ_PTR("ft_substr malloc fail returns NULL", res, NULL);

  TEST_END();
}

char *ft_strjoin(char const *s1, char const *s2);

static void test_strjoin(void) {

  TEST_START("ft_strjoin");
  
  char  *res;

  res = ft_strjoin("hello ", "world");
  ASSERT_EQ_STR("ft_strjoin(\"hello \", \"world\")", res, "hello world");
  free(res);

  res = ft_strjoin("", "world");
  ASSERT_EQ_STR("ft_strjoin(\"\", \"world\")", res, "world");
  free(res);

  res = ft_strjoin("hello", "");
  ASSERT_EQ_STR("ft_strjoin(\"hello\", \"\")", res, "hello");
  free(res);

  res = ft_strjoin("", "");
  ASSERT_EQ_STR("ft_strjoin(\"\", \"\")", res, "");
  free(res);

  res = ft_strjoin("a", "b");
  ASSERT_EQ_STR("ft_strjoin(\"a\", \"b\")", res, "ab");
  free(res);

  res = ft_strjoin("abc", "def");
  ASSERT_EQ_STR("ft_strjoin(\"abc\", \"def\")", res, "abcdef");
  free(res);

  res = ft_strjoin("hello world this is long", " and more");
  ASSERT_EQ_STR("ft_strjoin(\"hello world this is long\", \" and more\")", res, "hello world this is long and more");
  free(res);

  malloc_will_fail_after(0);
  res = ft_strjoin("hello", "world");
  malloc_reset();
  ASSERT_EQ_PTR("ft_strjoin malloc fail returns NULL", res, NULL);

  TEST_END();
}

char *ft_strtrim(char const *s1, char const *set);

static void test_strtrim(void) {
  TEST_START("ft_strtrim");
  
  char  *res;

  res = ft_strtrim("  hello  ", " ");
  ASSERT_EQ_STR("ft_strtrim(\"  hello  \", \" \")", res, "hello");
  free(res);

  res = ft_strtrim("xxhelloxx", "x");
  ASSERT_EQ_STR("ft_strtrim(\"xxhelloxx\", \"x\")", res, "hello");
  free(res);

  res = ft_strtrim("  hello  ", " h");
  ASSERT_EQ_STR("ft_strtrim(\"  hello  \", \" h\")", res, "ello");
  free(res);

  res = ft_strtrim("hello", "");
  ASSERT_EQ_STR("ft_strtrim(\"hello\", \"\")", res, "hello");
  free(res);

  res = ft_strtrim("", " ");
  ASSERT_EQ_STR("ft_strtrim(\"\", \" \")", res, "");
  free(res);

  res = ft_strtrim("   ", " ");
  ASSERT_EQ_STR("ft_strtrim(\"   \", \" \")", res, "");
  free(res);

  res = ft_strtrim("hello", "xyz");
  ASSERT_EQ_STR("ft_strtrim(\"hello\", \"xyz\")", res, "hello");
  free(res);

  res = ft_strtrim("abcba", "ab");
  ASSERT_EQ_STR("ft_strtrim(\"abcba\", \"ab\")", res, "c");
  free(res);

  res = ft_strtrim("  hello", " ");
  ASSERT_EQ_STR("ft_strtrim(\"  hello\", \" \")", res, "hello");
  free(res);

  res = ft_strtrim("hello  ", " ");
  ASSERT_EQ_STR("ft_strtrim(\"hello  \", \" \")", res, "hello");
  free(res);

  res = ft_strtrim("a", "a");
  ASSERT_EQ_STR("ft_strtrim(\"a\", \"a\")", res, "");
  free(res);

  res = ft_strtrim("a", "b");
  ASSERT_EQ_STR("ft_strtrim(\"a\", \"b\")", res, "a");
  free(res);

  res = ft_strtrim("\t \thello\t \t", " \t");
  ASSERT_EQ_STR("ft_strtrim(\"\\t \\thello\\t \\t\", \" \\t\")", res, "hello");
  free(res);

  malloc_will_fail_after(0);
  res = ft_strtrim("  hello  ", " ");
  malloc_reset();
  ASSERT_EQ_PTR("ft_strtrim malloc fail returns NULL", res, NULL);

  TEST_END();
}

char *ft_itoa(int n);

static void test_itoa(void) {
  TEST_START("ft_itoa");
  
  char  *res;

  res = ft_itoa(0);
  ASSERT_EQ_STR("ft_itoa(0)", res, "0");
  free(res);

  res = ft_itoa(42);
  ASSERT_EQ_STR("ft_itoa(42)", res, "42");
  free(res);

  res = ft_itoa(-42);
  ASSERT_EQ_STR("ft_itoa(-42)", res, "-42");
  free(res);

  res = ft_itoa(2147483647);
  ASSERT_EQ_STR("ft_itoa(2147483647)", res, "2147483647");
  free(res);

  res = ft_itoa(-2147483648);
  ASSERT_EQ_STR("ft_itoa(-2147483648)", res, "-2147483648");
  free(res);

  res = ft_itoa(1);
  ASSERT_EQ_STR("ft_itoa(1)", res, "1");
  free(res);

  res = ft_itoa(-1);
  ASSERT_EQ_STR("ft_itoa(-1)", res, "-1");
  free(res);

  res = ft_itoa(100);
  ASSERT_EQ_STR("ft_itoa(100)", res, "100");
  free(res);

  res = ft_itoa(-100);
  ASSERT_EQ_STR("ft_itoa(-100)", res, "-100");
  free(res);

  res = ft_itoa(9);
  ASSERT_EQ_STR("ft_itoa(9)", res, "9");
  free(res);

  res = ft_itoa(10);
  ASSERT_EQ_STR("ft_itoa(10)", res, "10");
  free(res);

  res = ft_itoa(-9);
  ASSERT_EQ_STR("ft_itoa(-9)", res, "-9");
  free(res);

  res = ft_itoa(-10);
  ASSERT_EQ_STR("ft_itoa(-10)", res, "-10");
  free(res);

  res = ft_itoa(1000000);
  ASSERT_EQ_STR("ft_itoa(1000000)", res, "1000000");
  free(res);

  malloc_will_fail_after(0);
  res = ft_itoa(42);
  malloc_reset();
  ASSERT_EQ_PTR("ft_itoa malloc fail returns NULL", res, NULL);

  TEST_END();
}

/////// FT_STRMAPI_START ///////

char *ft_strmapi(char const *s, char (*f)(unsigned int, char));

static char mapi_toupper(unsigned int i, char c) {
  (void)i;
  if (c >= 'a' && c <= 'z')
    return (c - 32);
  return (c);
}

static char mapi_add_index(unsigned int i, char c) {
  return (c + i);
}

static void test_strmapi(void) {
  TEST_START("ft_strmapi");
  
  char  *res;

  res = ft_strmapi("hello", mapi_toupper);
  ASSERT_EQ_STR("ft_strmapi(\"hello\", toupper)", res, "HELLO");
  free(res);

  res = ft_strmapi("", mapi_toupper);
  ASSERT_EQ_STR("ft_strmapi(\"\", toupper)", res, "");
  free(res);

  res = ft_strmapi("aaaa", mapi_add_index);
  ASSERT_EQ_STR("ft_strmapi(\"aaaa\", add_index)", res, "abcd");
  free(res);

  res = ft_strmapi("a", mapi_toupper);
  ASSERT_EQ_STR("ft_strmapi(\"a\", toupper)", res, "A");
  free(res);

  res = ft_strmapi("HELLO", mapi_toupper);
  ASSERT_EQ_STR("ft_strmapi(\"HELLO\", toupper)", res, "HELLO");
  free(res);

  malloc_will_fail_after(0);
  res = ft_strmapi("hello", mapi_toupper);
  malloc_reset();
  ASSERT_EQ_PTR("ft_strmapi malloc fail returns NULL", res, NULL);

  TEST_END();
}

/////// FT_STRMAPI_END ///////

/////// FT_STRITERI_START ///////

void ft_striteri(char *s, void (*f)(unsigned int, char *));

static void iteri_toupper(unsigned int i, char *c) {
  (void)i;
  if (*c >= 'a' && *c <= 'z')
    *c -= 32;
}

static void iteri_add_index(unsigned int i, char *c) {
  *c = *c + i;
}

static void test_striteri(void) {
  TEST_START("ft_striteri");

  char s1[] = "hello";
  char s2[] = "";
  char s3[] = "aaaa";
  char s4[] = "A";
  char s5[] = "abcde";

  ft_striteri(s1, iteri_toupper);
  ASSERT_EQ_STR("ft_striteri(\"hello\", toupper)", s1, "HELLO");

  ft_striteri(s2, iteri_toupper);
  ASSERT_EQ_STR("ft_striteri(\"\", toupper)", s2, "");

  ft_striteri(s3, iteri_add_index);
  ASSERT_EQ_STR("ft_striteri(\"aaaa\", add_index)", s3, "abcd");

  ft_striteri(s4, iteri_toupper);
  ASSERT_EQ_STR("ft_striteri(\"A\", toupper)", s4, "A");

  ft_striteri(s5, iteri_toupper);
  ASSERT_EQ_STR("ft_striteri(\"abcde\", toupper)", s5, "ABCDE");

  TEST_END();
}

/////// FT_STRITERI_END ///////

/////// FT_SPLIT_START ///////

char **ft_split(char const *s, char c);

static void free_split(char **arr) {
  int   i;
  i = 0;
  while (arr[i])
    free(arr[i++]);
  free(arr);
}

static int  count_split(char **arr) {
  int   i;
  i = 0;
  while (arr[i])
    i++;
  return (i);
}

static void test_split(void) {
  TEST_START("ft_split");
  
  char  **res;

  res = ft_split("hello world foo", ' ');
  ASSERT_EQ("ft_split(\"hello world foo\", ' ') count", count_split(res), 3);
  ASSERT_EQ_STR("ft_split(\"hello world foo\", ' ')[0]", res[0], "hello");
  ASSERT_EQ_STR("ft_split(\"hello world foo\", ' ')[1]", res[1], "world");
  ASSERT_EQ_STR("ft_split(\"hello world foo\", ' ')[2]", res[2], "foo");
  ASSERT_EQ_PTR("ft_split(\"hello world foo\", ' ')[3]", res[3], NULL);
  free_split(res);

  res = ft_split("  hello  world  ", ' ');
  ASSERT_EQ("ft_split(\"  hello  world  \", ' ') count", count_split(res), 2);
  ASSERT_EQ_STR("ft_split(\"  hello  world  \", ' ')[0]", res[0], "hello");
  ASSERT_EQ_STR("ft_split(\"  hello  world  \", ' ')[1]", res[1], "world");
  free_split(res);

  res = ft_split("hello", ' ');
  ASSERT_EQ("ft_split(\"hello\", ' ') count", count_split(res), 1);
  ASSERT_EQ_STR("ft_split(\"hello\", ' ')[0]", res[0], "hello");
  free_split(res);

  res = ft_split("", ' ');
  ASSERT_EQ("ft_split(\"\", ' ') count", count_split(res), 0);
  ASSERT_EQ_PTR("ft_split(\"\", ' ')[0]", res[0], NULL);
  free_split(res);

  res = ft_split("   ", ' ');
  ASSERT_EQ("ft_split(\"   \", ' ') count", count_split(res), 0);
  free_split(res);

  res = ft_split("a,b,,c,", ',');
  ASSERT_EQ("ft_split(\"a,b,,c,\", ',') count", count_split(res), 3);
  ASSERT_EQ_STR("ft_split(\"a,b,,c,\", ',')[0]", res[0], "a");
  ASSERT_EQ_STR("ft_split(\"a,b,,c,\", ',')[1]", res[1], "b");
  ASSERT_EQ_STR("ft_split(\"a,b,,c,\", ',')[2]", res[2], "c");
  free_split(res);

  res = ft_split("a", ' ');
  ASSERT_EQ("ft_split(\"a\", ' ') count", count_split(res), 1);
  ASSERT_EQ_STR("ft_split(\"a\", ' ')[0]", res[0], "a");
  free_split(res);

  res = ft_split("one", ',');
  ASSERT_EQ("ft_split(\"one\", ',') count", count_split(res), 1);
  ASSERT_EQ_STR("ft_split(\"one\", ',')[0]", res[0], "one");
  free_split(res);

  res = ft_split(",a,", ',');
  ASSERT_EQ("ft_split(\",a,\", ',') count", count_split(res), 1);
  ASSERT_EQ_STR("ft_split(\",a,\", ',')[0]", res[0], "a");
  free_split(res);

  res = ft_split("abc def ghi jkl mno", ' ');
  ASSERT_EQ("ft_split(\"abc def ghi jkl mno\", ' ') count", count_split(res), 5);
  ASSERT_EQ_STR("ft_split(\"abc def ghi jkl mno\", ' ')[0]", res[0], "abc");
  ASSERT_EQ_STR("ft_split(\"abc def ghi jkl mno\", ' ')[4]", res[4], "mno");
  free_split(res);

  res = ft_split(",,a,,b,,c,,", ',');
  ASSERT_EQ("ft_split(\",,a,,b,,c,,\", ',') count", count_split(res), 3);
  ASSERT_EQ_STR("ft_split(\",,a,,b,,c,,\", ',')[0]", res[0], "a");
  ASSERT_EQ_STR("ft_split(\",,a,,b,,c,,\", ',')[1]", res[1], "b");
  ASSERT_EQ_STR("ft_split(\",,a,,b,,c,,\", ',')[2]", res[2], "c");
  free_split(res);

  malloc_will_fail_after(0);
  res = ft_split("hello world", ' ');
  malloc_reset();
  ASSERT_EQ_PTR("ft_split malloc fail on array returns NULL", res, NULL);

  track_allocs_start();
  malloc_will_fail_after(3);
  res = ft_split("a b c", ' ');
  malloc_reset();
  track_allocs_stop();
  ASSERT_EQ_PTR("ft_split malloc fail mid-word returns NULL", res, NULL);
  ASSERT_EQ("ft_split malloc fail mid-word no leaks", track_leaks(), 0);

  TEST_END();
}

/////// FT_SPLIT_END ///////

void ft_putchar_fd(char c, int fd);

static void test_putchar_fd(void) {
  TEST_START("ft_putchar_fd");
  
  int           pfd[2];
  char  buf[2];
  int           rd;

  pipe(pfd);
  ft_putchar_fd('A', pfd[1]);
  close(pfd[1]);
  rd = read(pfd[0], buf, 2);
  close(pfd[0]);
  ASSERT_EQ("ft_putchar_fd('A', fd) len", rd, 1);
  ASSERT_EQ("ft_putchar_fd('A', fd) char", buf[0], 'A');

  pipe(pfd);
  ft_putchar_fd('\0', pfd[1]);
  close(pfd[1]);
  rd = read(pfd[0], buf, 2);
  close(pfd[0]);
  ASSERT_EQ("ft_putchar_fd('\\0', fd) len", rd, 1);
  ASSERT_EQ("ft_putchar_fd('\\0', fd) char", buf[0], '\0');

  pipe(pfd);
  ft_putchar_fd('\n', pfd[1]);
  close(pfd[1]);
  rd = read(pfd[0], buf, 2);
  close(pfd[0]);
  ASSERT_EQ("ft_putchar_fd('\\n', fd) len", rd, 1);
  ASSERT_EQ("ft_putchar_fd('\\n', fd) char", buf[0], '\n');

  pipe(pfd);
  ft_putchar_fd('z', pfd[1]);
  close(pfd[1]);
  rd = read(pfd[0], buf, 2);
  close(pfd[0]);
  ASSERT_EQ("ft_putchar_fd('z', fd) char", buf[0], 'z');

  TEST_END();
}

void ft_putstr_fd(char *s, int fd);

static void test_putstr_fd(void) {
  TEST_START("ft_putstr_fd");
  
  int           pfd[2];
  char  buf[64];
  int           rd;

  pipe(pfd);
  ft_putstr_fd("hello", pfd[1]);
  close(pfd[1]);
  rd = read(pfd[0], buf, 64);
  close(pfd[0]);
  buf[rd] = '\0';
  ASSERT_EQ("ft_putstr_fd(\"hello\", fd) len", rd, 5);
  ASSERT_EQ_STR("ft_putstr_fd(\"hello\", fd) content", buf, "hello");

  pipe(pfd);
  ft_putstr_fd("", pfd[1]);
  close(pfd[1]);
  rd = read(pfd[0], buf, 64);
  close(pfd[0]);
  ASSERT_EQ("ft_putstr_fd(\"\", fd) len", rd, 0);

  pipe(pfd);
  ft_putstr_fd("a longer test string", pfd[1]);
  close(pfd[1]);
  rd = read(pfd[0], buf, 64);
  close(pfd[0]);
  buf[rd] = '\0';
  ASSERT_EQ("ft_putstr_fd(\"a longer test string\", fd) len", rd, 20);
  ASSERT_EQ_STR("ft_putstr_fd(\"a longer test string\", fd) content", buf, "a longer test string");

  TEST_END();
}

void ft_putendl_fd(char *s, int fd);

static void test_putendl_fd(void) {
  TEST_START("ft_putendl_fd");
  
  int           pfd[2];
  char  buf[64];
  int           rd;

  pipe(pfd);
  ft_putendl_fd("hello", pfd[1]);
  close(pfd[1]);
  rd = read(pfd[0], buf, 64);
  close(pfd[0]);
  buf[rd] = '\0';
  ASSERT_EQ("ft_putendl_fd(\"hello\", fd) len", rd, 6);
  ASSERT_EQ_STR("ft_putendl_fd(\"hello\", fd) content", buf, "hello\n");

  pipe(pfd);
  ft_putendl_fd("", pfd[1]);
  close(pfd[1]);
  rd = read(pfd[0], buf, 64);
  close(pfd[0]);
  buf[rd] = '\0';
  ASSERT_EQ("ft_putendl_fd(\"\", fd) len", rd, 1);
  ASSERT_EQ_STR("ft_putendl_fd(\"\", fd) content", buf, "\n");

  TEST_END();
}

void ft_putnbr_fd(int n, int fd);

static void test_putnbr_fd(void) {
  TEST_START("ft_putnbr_fd");
  
  int           pfd[2];
  char  buf[64];
  int           rd;

  pipe(pfd);
  ft_putnbr_fd(42, pfd[1]);
  close(pfd[1]);
  rd = read(pfd[0], buf, 64);
  close(pfd[0]);
  buf[rd] = '\0';
  ASSERT_EQ_STR("ft_putnbr_fd(42, fd)", buf, "42");

  pipe(pfd);
  ft_putnbr_fd(-42, pfd[1]);
  close(pfd[1]);
  rd = read(pfd[0], buf, 64);
  close(pfd[0]);
  buf[rd] = '\0';
  ASSERT_EQ_STR("ft_putnbr_fd(-42, fd)", buf, "-42");

  pipe(pfd);
  ft_putnbr_fd(0, pfd[1]);
  close(pfd[1]);
  rd = read(pfd[0], buf, 64);
  close(pfd[0]);
  buf[rd] = '\0';
  ASSERT_EQ_STR("ft_putnbr_fd(0, fd)", buf, "0");

  pipe(pfd);
  ft_putnbr_fd(2147483647, pfd[1]);
  close(pfd[1]);
  rd = read(pfd[0], buf, 64);
  close(pfd[0]);
  buf[rd] = '\0';
  ASSERT_EQ_STR("ft_putnbr_fd(2147483647, fd)", buf, "2147483647");

  pipe(pfd);
  ft_putnbr_fd(-2147483648, pfd[1]);
  close(pfd[1]);
  rd = read(pfd[0], buf, 64);
  close(pfd[0]);
  buf[rd] = '\0';
  ASSERT_EQ_STR("ft_putnbr_fd(-2147483648, fd)", buf, "-2147483648");

  pipe(pfd);
  ft_putnbr_fd(5, pfd[1]);
  close(pfd[1]);
  rd = read(pfd[0], buf, 64);
  close(pfd[0]);
  buf[rd] = '\0';
  ASSERT_EQ_STR("ft_putnbr_fd(5, fd)", buf, "5");

  pipe(pfd);
  ft_putnbr_fd(-5, pfd[1]);
  close(pfd[1]);
  rd = read(pfd[0], buf, 64);
  close(pfd[0]);
  buf[rd] = '\0';
  ASSERT_EQ_STR("ft_putnbr_fd(-5, fd)", buf, "-5");

  pipe(pfd);
  ft_putnbr_fd(10, pfd[1]);
  close(pfd[1]);
  rd = read(pfd[0], buf, 64);
  close(pfd[0]);
  buf[rd] = '\0';
  ASSERT_EQ_STR("ft_putnbr_fd(10, fd)", buf, "10");

  pipe(pfd);
  ft_putnbr_fd(-10, pfd[1]);
  close(pfd[1]);
  rd = read(pfd[0], buf, 64);
  close(pfd[0]);
  buf[rd] = '\0';
  ASSERT_EQ_STR("ft_putnbr_fd(-10, fd)", buf, "-10");

  TEST_END();
}

/////// T_LIST START ///////

typedef struct s_list {
  void *content;
  struct s_list	*next;
} t_list;

t_list *ft_lstnew(void *content);

static void test_lstnew(void) {
  TEST_START("ft_lstnew");
  
  t_list        *node;
  int           val;

  val = 42;
  node = ft_lstnew(&val);
  ASSERT_EQ_PTR("ft_lstnew(&val)->content", node->content, &val);
  ASSERT_EQ_PTR("ft_lstnew(&val)->next", node->next, NULL);
  ASSERT_EQ("*(int *)ft_lstnew(&val)->content", *(int *)node->content, 42);
  free(node);

  node = ft_lstnew(NULL);
  ASSERT_EQ_PTR("ft_lstnew(NULL)->content", node->content, NULL);
  ASSERT_EQ_PTR("ft_lstnew(NULL)->next", node->next, NULL);
  free(node);

  node = ft_lstnew("hello");
  ASSERT_EQ_STR("ft_lstnew(\"hello\")->content", (char *)node->content, "hello");
  free(node);

  TEST_END();
}

void ft_lstadd_front(t_list **lst, t_list *new);

static void test_lstadd_front(void) {
  TEST_START("ft_lstadd_front");
  
  t_list        *lst;
  t_list        *n1;
  t_list        *n2;

  lst = NULL;
  n1 = ft_lstnew("first");
  ft_lstadd_front(&lst, n1);
  ASSERT_EQ_PTR("ft_lstadd_front(&NULL, n1) head", lst, n1);
  ASSERT_EQ_PTR("ft_lstadd_front(&NULL, n1)->next", lst->next, NULL);

  n2 = ft_lstnew("second");
  ft_lstadd_front(&lst, n2);
  ASSERT_EQ_PTR("ft_lstadd_front(&lst, n2) head", lst, n2);
  ASSERT_EQ_PTR("ft_lstadd_front(&lst, n2)->next", lst->next, n1);
  ASSERT_EQ_STR("ft_lstadd_front head->content", (char *)lst->content, "second");
  ASSERT_EQ_STR("ft_lstadd_front head->next->content", (char *)lst->next->content, "first");

  free(n1);
  free(n2);

  TEST_END();
}

int ft_lstsize(t_list *lst);

static void test_lstsize(void) {
  TEST_START("ft_lstsize");
  
  t_list        *n1;
  t_list        *n2;
  t_list        *n3;

  ASSERT_EQ("ft_lstsize(NULL)", ft_lstsize(NULL), 0);

  n1 = ft_lstnew("a");
  ASSERT_EQ("ft_lstsize([a])", ft_lstsize(n1), 1);

  n2 = ft_lstnew("b");
  n3 = ft_lstnew("c");
  n1->next = n2;
  n2->next = n3;
  ASSERT_EQ("ft_lstsize([a->b->c])", ft_lstsize(n1), 3);

  free(n1);
  free(n2);
  free(n3);
  
  TEST_END();
}

t_list	*ft_lstlast(t_list *lst);

static void test_lstlast(void) {
  TEST_START("ft_lstlast");
  
  t_list        *n1;
  t_list        *n2;
  t_list        *n3;

  ASSERT_EQ_PTR("ft_lstlast(NULL)", ft_lstlast(NULL), NULL);

  n1 = ft_lstnew("a");
  ASSERT_EQ_PTR("ft_lstlast([a])", ft_lstlast(n1), n1);

  n2 = ft_lstnew("b");
  n3 = ft_lstnew("c");
  n1->next = n2;
  n2->next = n3;
  ASSERT_EQ_PTR("ft_lstlast([a->b->c]) ptr", ft_lstlast(n1), n3);
  ASSERT_EQ_STR("ft_lstlast([a->b->c])->content", (char *)ft_lstlast(n1)->content, "c");

  free(n1);
  free(n2);
  free(n3);

  TEST_END();
}

void ft_lstadd_back(t_list **lst, t_list *new);

static void test_lstadd_back(void) {
  TEST_START("ft_lstadd_back");
  
  t_list        *lst;
  t_list        *n1;
  t_list        *n2;
  t_list        *n3;

  lst = NULL;
  n1 = ft_lstnew("first");
  ft_lstadd_back(&lst, n1);
  ASSERT_EQ_PTR("ft_lstadd_back(&NULL, n1) head", lst, n1);

  n2 = ft_lstnew("second");
  ft_lstadd_back(&lst, n2);
  ASSERT_EQ_PTR("ft_lstadd_back(&lst, n2) head unchanged", lst, n1);
  ASSERT_EQ_PTR("ft_lstadd_back(&lst, n2) tail", lst->next, n2);

  n3 = ft_lstnew("third");
  ft_lstadd_back(&lst, n3);
  ASSERT_EQ_PTR("ft_lstadd_back(&lst, n3) tail", lst->next->next, n3);
  ASSERT_EQ_STR("ft_lstlast after lstadd_back->content", (char *)ft_lstlast(lst)->content, "third");

  free(n1);
  free(n2);
  free(n3);
  
  TEST_END();
}

/////// FT_LSTDELONE_START ///////

void ft_lstdelone(t_list *lst, void (*del)(void *));

static int  g_del_called = 0;

static void mock_del(void *content) {
  free(content);
  g_del_called++;
}

static void test_lstdelone(void) {
  TEST_START("ft_lstdelone");
  
  t_list        *node;
  char  *s;

  g_del_called = 0;
  s = strdup("hello");
  node = ft_lstnew(s);
  ft_lstdelone(node, mock_del);
  ASSERT_EQ("ft_lstdelone(node, del) del called", g_del_called, 1);

  {
    t_list      *n1;
    t_list      *n2;

    g_del_called = 0;
    n1 = ft_lstnew(strdup("first"));
    n2 = ft_lstnew(strdup("second"));
    n1->next = n2;
    ft_lstdelone(n1, mock_del);
    ASSERT_EQ("ft_lstdelone(n1, del) keeps next", g_del_called, 1);
    ASSERT_EQ_STR("ft_lstdelone(n1, del) n2->content", (char *)n2->content, "second");
    ft_lstdelone(n2, mock_del);
  }
  TEST_END();
}

/////// FT_LSTDELONE_END ///////

void ft_lstclear(t_list **lst, void (*del)(void *));

static void     test_lstclear(void) {
  TEST_START("ft_lstclear");
  
  t_list    *lst;

  g_del_called = 0;
  lst = ft_lstnew(strdup("a"));
  lst->next = ft_lstnew(strdup("b"));
  lst->next->next = ft_lstnew(strdup("c"));

  ft_lstclear(&lst, mock_del);
  ASSERT_EQ_PTR("ft_lstclear([a->b->c]) sets NULL", lst, NULL);
  ASSERT_EQ("ft_lstclear([a->b->c]) del count", g_del_called, 3);

  g_del_called = 0;
  lst = ft_lstnew(strdup("only"));
  ft_lstclear(&lst, mock_del);
  ASSERT_EQ_PTR("ft_lstclear([only]) sets NULL", lst, NULL);
  ASSERT_EQ("ft_lstclear([only]) del count", g_del_called, 1);
  TEST_END();
}

/////// FT_LSTITER_START ///////

void ft_lstiter(t_list *lst, void (*f)(void *));

static int  g_iter_count = 0;

static void iter_counter(void *content)
{
  (void)content;
  g_iter_count++;
}

static void test_lstiter(void)
{
  TEST_START("ft_lstiter");
  
  t_list    *n1;
  t_list    *n2;
  t_list    *n3;


  g_iter_count = 0;
  n1 = ft_lstnew("a");
  n2 = ft_lstnew("b");
  n3 = ft_lstnew("c");
  n1->next = n2;
  n2->next = n3;

  ft_lstiter(n1, iter_counter);
  ASSERT_EQ("ft_lstiter([a->b->c], counter) count", g_iter_count, 3);

  g_iter_count = 0;
  ft_lstiter(NULL, iter_counter);
  ASSERT_EQ("ft_lstiter(NULL, counter) count", g_iter_count, 0);

  free(n1);
  free(n2);
  free(n3);

  {
    t_list  *single;

    g_iter_count = 0;
    single = ft_lstnew("only");
    ft_lstiter(single, iter_counter);
    ASSERT_EQ("ft_lstiter([only], counter) count", g_iter_count, 1);
    free(single);
  }
  TEST_END();
}

/////// FT_LSTITER_END ///////

/////// FT_LSTMAP_START ///////

t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

static void *map_dup(void *content) {
  char *s = (char *)content;
  size_t len = strlen(s) + 1;
  char *dup = malloc(len);
  if (dup)
    memcpy(dup, s, len);
  return (dup);
}

static void test_lstmap(void)
{

  TEST_START("ft_lstmap");
    
  t_list    *src;
  t_list    *mapped;
  t_list    *tmp;

  src = ft_lstnew("hello");
  src->next = ft_lstnew("world");
  src->next->next = ft_lstnew("!");

  mapped = ft_lstmap(src, map_dup, free);
  ASSERT_EQ("ft_lstmap([hello->world->!], dup) size", ft_lstsize(mapped), 3);
  ASSERT_EQ_STR("ft_lstmap(...)[0]->content", (char *)mapped->content, "hello");
  ASSERT_EQ_STR("ft_lstmap(...)[1]->content", (char *)mapped->next->content, "world");
  ASSERT_EQ_STR("ft_lstmap(...)[2]->content", (char *)mapped->next->next->content, "!");

  tmp = mapped;
  while (tmp)
    {
      ASSERT_EQ("ft_lstmap content is new alloc",
                (tmp->content != src->content)
                && (tmp->content != src->next->content)
                && (tmp->content != src->next->next->content), 1);
      tmp = tmp->next;
    }

  ft_lstclear(&mapped, free);
  ASSERT_EQ_PTR("ft_lstclear(&mapped) sets NULL", mapped, NULL);

  mapped = ft_lstmap(NULL, map_dup, free);
  ASSERT_EQ_PTR("ft_lstmap(NULL, dup, free)", mapped, NULL);

  free(src->next->next);
  free(src->next);
  free(src);

  {
    t_list  *s1;
    t_list  *m1;

    s1 = ft_lstnew("solo");
    m1 = ft_lstmap(s1, map_dup, free);
    ASSERT_EQ("ft_lstmap([solo], dup) size", ft_lstsize(m1), 1);
    ASSERT_EQ_STR("ft_lstmap([solo], dup)->content", (char *)m1->content, "solo");
    ASSERT_EQ_PTR("ft_lstmap([solo], dup)->next", m1->next, NULL);
    ft_lstclear(&m1, free);
    free(s1);
  }

  {
    t_list  *s1;
    t_list  *res;

    s1 = ft_lstnew("aaa");
    s1->next = ft_lstnew("bbb");
    s1->next->next = ft_lstnew("ccc");

    track_allocs_start();
    malloc_will_fail_after(3);
    res = ft_lstmap(s1, map_dup, free);
    malloc_reset();
    track_allocs_stop();
    ASSERT_EQ_PTR("ft_lstmap malloc fail mid-map returns NULL", res, NULL);
    ASSERT_EQ("ft_lstmap malloc fail mid-map no leaks", track_leaks(), 0);

    free(s1->next->next);
    free(s1->next);
    free(s1);
  }

  TEST_END();
}

/////// FT_LSTMAP_END ///////

//////////////////////////////////////////////////////////////
// TEST ENTRIES                                             // 
//////////////////////////////////////////////////////////////

typedef struct s_test_entry
{
  const char    *name;
  void  (*func)(void);
  int       available;
}  t_test_entry;

static const t_test_entry   g_tests[] = {
  {"ft_isalpha", test_isalpha, AVAIL_ft_isalpha},
  {"ft_isdigit", test_isdigit, AVAIL_ft_isdigit},
  {"ft_isalnum", test_isalnum, AVAIL_ft_isalnum},
  {"ft_isascii", test_isascii, AVAIL_ft_isascii},
  {"ft_isprint", test_isprint, AVAIL_ft_isprint},
  {"ft_toupper", test_toupper, AVAIL_ft_toupper},
  {"ft_tolower", test_tolower, AVAIL_ft_tolower},
  {"ft_strlen", test_strlen, AVAIL_ft_strlen},
  {"ft_memset", test_memset, AVAIL_ft_memset},
  {"ft_bzero", test_bzero, AVAIL_ft_bzero},
  {"ft_memcpy", test_memcpy, AVAIL_ft_memcpy},
  {"ft_memmove", test_memmove, AVAIL_ft_memmove},
  {"ft_memcmp", test_memcmp, AVAIL_ft_memcmp},
  {"ft_memchr", test_memchr, AVAIL_ft_memchr},
  {"ft_strncmp", test_strncmp, AVAIL_ft_strncmp},
  {"ft_atoi", test_atoi, AVAIL_ft_atoi},
  {"ft_strdup", test_strdup, AVAIL_ft_strdup},
  {"ft_calloc", test_calloc, AVAIL_ft_calloc},
  {"ft_strchr", test_strchr, AVAIL_ft_strchr},
  {"ft_strrchr", test_strrchr, AVAIL_ft_strrchr},
  {"ft_strlcpy", test_strlcpy, AVAIL_ft_strlcpy},
  {"ft_strlcat", test_strlcat, AVAIL_ft_strlcat},
  {"ft_strnstr", test_strnstr, AVAIL_ft_strnstr},
  {"ft_substr", test_substr, AVAIL_ft_substr},
  {"ft_strjoin", test_strjoin, AVAIL_ft_strjoin},
  {"ft_strtrim", test_strtrim, AVAIL_ft_strtrim},
  {"ft_itoa", test_itoa, AVAIL_ft_itoa},
  {"ft_strmapi", test_strmapi, AVAIL_ft_strmapi},
  {"ft_striteri", test_striteri, AVAIL_ft_striteri},
  {"ft_split", test_split, AVAIL_ft_split},
  {"ft_putchar_fd", test_putchar_fd, AVAIL_ft_putchar_fd},
  {"ft_putstr_fd", test_putstr_fd, AVAIL_ft_putstr_fd},
  {"ft_putendl_fd", test_putendl_fd, AVAIL_ft_putendl_fd},
  {"ft_putnbr_fd", test_putnbr_fd, AVAIL_ft_putnbr_fd},
  {"ft_lstnew", test_lstnew, AVAIL_ft_lstnew},
  {"ft_lstadd_front", test_lstadd_front, AVAIL_ft_lstadd_front},
  {"ft_lstsize", test_lstsize, AVAIL_ft_lstsize},
  {"ft_lstlast", test_lstlast, AVAIL_ft_lstlast},
  {"ft_lstadd_back", test_lstadd_back, AVAIL_ft_lstadd_back},
  {"ft_lstdelone", test_lstdelone, AVAIL_ft_lstdelone},
  {"ft_lstclear", test_lstclear, AVAIL_ft_lstclear},
  {"ft_lstiter", test_lstiter, AVAIL_ft_lstiter},
  {"ft_lstmap", test_lstmap, AVAIL_ft_lstmap},
};

//////////////////////////////////////////////////////////////
// ENTRY POINT                                              // 
//////////////////////////////////////////////////////////////

int main(int argc, char **argv) {
  int n_tests;
  int found;
  int i;

  PRINT_LOGO();
  
  n_tests = sizeof(g_tests) / sizeof(g_tests[0]);  

  // run a specific test given as argument
  if (argc > 1) {
    g_verbose = 1;
    char *test_name = argv[1];
    found = 0;
    while (i < n_tests) {
      if (strcmp(test_name, g_tests[i].name) == 0) {
        found = 1;
        if (g_tests[i].available)
          g_tests[i].func();
        else
          TEST_SKIP(g_tests[i].name);
      }
      i++;
    }
    if (!found)
      printf(RED " unknown function: %s" RESET "\n", argv[i]);  
  }

  // run all tests 
  else if (argc == 1) {
    g_total_suites = n_tests;
    i = 0;
    while (i < n_tests) {
      if (g_tests[i].available)
        g_tests[i].func();
      else
        TEST_SKIP(g_tests[i].name);
      i++;
    }
  }
  
  TEST_SUMMARY();
  return 0;    
}
