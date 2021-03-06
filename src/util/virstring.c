/*
 * Copyright (C) 2012-2013 Red Hat, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * Authors:
 *     Daniel P. Berrange <berrange@redhat.com>
 */

#include <config.h>

#include <stdlib.h>
#include <stdio.h>

#include "c-ctype.h"
#include "virstring.h"
#include "viralloc.h"
#include "virbuffer.h"
#include "virerror.h"

#define VIR_FROM_THIS VIR_FROM_NONE

/*
 * The following virStringSplit & virStringJoin methods
 * are derived from g_strsplit / g_strjoin in glib2,
 * also available under the LGPLv2+ license terms
 */

/**
 * virStringSplit:
 * @string: a string to split
 * @delim: a string which specifies the places at which to split
 *     the string. The delimiter is not included in any of the resulting
 *     strings, unless @max_tokens is reached.
 * @max_tokens: the maximum number of pieces to split @string into.
 *     If this is 0, the string is split completely.
 *
 * Splits a string into a maximum of @max_tokens pieces, using the given
 * @delim. If @max_tokens is reached, the remainder of @string is
 * appended to the last token.
 *
 * As a special case, the result of splitting the empty string "" is an empty
 * vector, not a vector containing a single string. The reason for this
 * special case is that being able to represent a empty vector is typically
 * more useful than consistent handling of empty elements. If you do need
 * to represent empty elements, you'll need to check for the empty string
 * before calling virStringSplit().
 *
 * Return value: a newly-allocated NULL-terminated array of strings. Use
 *    virStringFreeList() to free it.
 */
char **virStringSplit(const char *string,
                      const char *delim,
                      size_t max_tokens)
{
    char **tokens = NULL;
    size_t ntokens = 0;
    size_t maxtokens = 0;
    const char *remainder = string;
    char *tmp;
    size_t i;

    if (max_tokens == 0)
        max_tokens = INT_MAX;

    tmp = strstr(remainder, delim);
    if (tmp) {
        size_t delimlen = strlen(delim);

        while (--max_tokens && tmp) {
            size_t len = tmp - remainder;

            if (VIR_RESIZE_N(tokens, maxtokens, ntokens, 1) < 0)
                goto error;

            if (VIR_STRNDUP(tokens[ntokens], remainder, len) < 0)
                goto error;
            ntokens++;
            remainder = tmp + delimlen;
            tmp = strstr(remainder, delim);
        }
    }
    if (*string) {
        if (VIR_RESIZE_N(tokens, maxtokens, ntokens, 1) < 0)
            goto error;

        if (VIR_STRDUP(tokens[ntokens], remainder) < 0)
            goto error;
        ntokens++;
    }

    if (VIR_RESIZE_N(tokens, maxtokens, ntokens, 1) < 0)
        goto error;
    tokens[ntokens++] = NULL;

    return tokens;

error:
    for (i = 0; i < ntokens; i++)
        VIR_FREE(tokens[i]);
    VIR_FREE(tokens);
    return NULL;
}


/**
 * virStringJoin:
 * @strings: a NULL-terminated array of strings to join
 * @delim: a string to insert between each of the strings
 *
 * Joins a number of strings together to form one long string, with the
 * @delim inserted between each of them. The returned string
 * should be freed with VIR_FREE().
 *
 * Returns: a newly-allocated string containing all of the strings joined
 *     together, with @delim between them
 */
char *virStringJoin(const char **strings,
                    const char *delim)
{
    char *ret;
    virBuffer buf = VIR_BUFFER_INITIALIZER;
    while (*strings) {
        virBufferAdd(&buf, *strings, -1);
        if (*(strings+1))
            virBufferAdd(&buf, delim, -1);
        strings++;
    }
    if (virBufferError(&buf)) {
        virReportOOMError();
        return NULL;
    }
    ret = virBufferContentAndReset(&buf);
    if (!ret)
        ignore_value(VIR_STRDUP(ret, ""));
    return ret;
}


/**
 * virStringFreeList:
 * @str_array: a NULL-terminated array of strings to free
 *
 * Frees a NULL-terminated array of strings, and the array itself.
 * If called on a NULL value, virStringFreeList() simply returns.
 */
void virStringFreeList(char **strings)
{
    char **tmp = strings;
    while (tmp && *tmp) {
        VIR_FREE(*tmp);
        tmp++;
    }
    VIR_FREE(strings);
}


bool
virStringArrayHasString(char **strings, const char *needle)
{
    size_t i = 0;

    if (!strings)
        return false;

    while (strings[i]) {
        if (STREQ(strings[i++], needle))
            return true;
    }

    return false;
}

/* Like strtol, but produce an "int" result, and check more carefully.
   Return 0 upon success;  return -1 to indicate failure.
   When END_PTR is NULL, the byte after the final valid digit must be NUL.
   Otherwise, it's like strtol and lets the caller check any suffix for
   validity.  This function is careful to return -1 when the string S
   represents a number that is not representable as an "int". */
int
virStrToLong_i(char const *s, char **end_ptr, int base, int *result)
{
    long int val;
    char *p;
    int err;

    errno = 0;
    val = strtol(s, &p, base); /* exempt from syntax-check */
    err = (errno || (!end_ptr && *p) || p == s || (int) val != val);
    if (end_ptr)
        *end_ptr = p;
    if (err)
        return -1;
    *result = val;
    return 0;
}

/* Just like virStrToLong_i, above, but produce an "unsigned int" value.  */
int
virStrToLong_ui(char const *s, char **end_ptr, int base, unsigned int *result)
{
    unsigned long int val;
    char *p;
    int err;

    errno = 0;
    val = strtoul(s, &p, base); /* exempt from syntax-check */
    err = (errno || (!end_ptr && *p) || p == s || (unsigned int) val != val);
    if (end_ptr)
        *end_ptr = p;
    if (err)
        return -1;
    *result = val;
    return 0;
}

/* Just like virStrToLong_i, above, but produce a "long" value.  */
int
virStrToLong_l(char const *s, char **end_ptr, int base, long *result)
{
    long int val;
    char *p;
    int err;

    errno = 0;
    val = strtol(s, &p, base); /* exempt from syntax-check */
    err = (errno || (!end_ptr && *p) || p == s);
    if (end_ptr)
        *end_ptr = p;
    if (err)
        return -1;
    *result = val;
    return 0;
}

/* Just like virStrToLong_i, above, but produce an "unsigned long" value.  */
int
virStrToLong_ul(char const *s, char **end_ptr, int base, unsigned long *result)
{
    unsigned long int val;
    char *p;
    int err;

    errno = 0;
    val = strtoul(s, &p, base); /* exempt from syntax-check */
    err = (errno || (!end_ptr && *p) || p == s);
    if (end_ptr)
        *end_ptr = p;
    if (err)
        return -1;
    *result = val;
    return 0;
}

/* Just like virStrToLong_i, above, but produce a "long long" value.  */
int
virStrToLong_ll(char const *s, char **end_ptr, int base, long long *result)
{
    long long val;
    char *p;
    int err;

    errno = 0;
    val = strtoll(s, &p, base); /* exempt from syntax-check */
    err = (errno || (!end_ptr && *p) || p == s);
    if (end_ptr)
        *end_ptr = p;
    if (err)
        return -1;
    *result = val;
    return 0;
}

/* Just like virStrToLong_i, above, but produce an "unsigned long long" value.  */
int
virStrToLong_ull(char const *s, char **end_ptr, int base, unsigned long long *result)
{
    unsigned long long val;
    char *p;
    int err;

    errno = 0;
    val = strtoull(s, &p, base); /* exempt from syntax-check */
    err = (errno || (!end_ptr && *p) || p == s);
    if (end_ptr)
        *end_ptr = p;
    if (err)
        return -1;
    *result = val;
    return 0;
}

int
virStrToDouble(char const *s,
               char **end_ptr,
               double *result)
{
    double val;
    char *p;
    int err;

    errno = 0;
    val = strtod(s, &p); /* exempt from syntax-check */
    err = (errno || (!end_ptr && *p) || p == s);
    if (end_ptr)
        *end_ptr = p;
    if (err)
        return -1;
    *result = val;
    return 0;
}

int
virVasprintfInternal(bool report,
                     int domcode,
                     const char *filename,
                     const char *funcname,
                     size_t linenr,
                     char **strp,
                     const char *fmt,
                     va_list list)
{
    int ret;

    if ((ret = vasprintf(strp, fmt, list)) == -1) {
        if (report)
            virReportOOMErrorFull(domcode, filename, funcname, linenr);
        *strp = NULL;
    }
    return ret;
}

int
virAsprintfInternal(bool report,
                    int domcode,
                    const char *filename,
                    const char *funcname,
                    size_t linenr,
                    char **strp,
                    const char *fmt, ...)
{
    va_list ap;
    int ret;

    va_start(ap, fmt);
    ret = virVasprintfInternal(report, domcode, filename,
                               funcname, linenr, strp, fmt, ap);
    va_end(ap);
    return ret;
}

/**
 * virStrncpy
 *
 * A safe version of strncpy.  The last parameter is the number of bytes
 * available in the destination string, *not* the number of bytes you want
 * to copy.  If the destination is not large enough to hold all n of the
 * src string bytes plus a \0, NULL is returned and no data is copied.
 * If the destination is large enough to hold the n bytes plus \0, then the
 * string is copied and a pointer to the destination string is returned.
 */
char *
virStrncpy(char *dest, const char *src, size_t n, size_t destbytes)
{
    char *ret;

    if (n > (destbytes - 1))
        return NULL;

    ret = strncpy(dest, src, n);
    /* strncpy NULL terminates iff the last character is \0.  Therefore
     * force the last byte to be \0
     */
    dest[n] = '\0';

    return ret;
}

/**
 * virStrcpy
 *
 * A safe version of strcpy.  The last parameter is the number of bytes
 * available in the destination string, *not* the number of bytes you want
 * to copy.  If the destination is not large enough to hold all n of the
 * src string bytes plus a \0, NULL is returned and no data is copied.
 * If the destination is large enough to hold the source plus \0, then the
 * string is copied and a pointer to the destination string is returned.
 */
char *
virStrcpy(char *dest, const char *src, size_t destbytes)
{
    return virStrncpy(dest, src, strlen(src), destbytes);
}

/**
 * virSkipSpaces:
 * @str: pointer to the char pointer used
 *
 * Skip potential blanks, this includes space tabs, line feed,
 * carriage returns.
 */
void
virSkipSpaces(const char **str)
{
    const char *cur = *str;

    while (c_isspace(*cur))
        cur++;
    *str = cur;
}

/**
 * virSkipSpacesAndBackslash:
 * @str: pointer to the char pointer used
 *
 * Like virSkipSpaces, but also skip backslashes erroneously emitted
 * by xend
 */
void
virSkipSpacesAndBackslash(const char **str)
{
    const char *cur = *str;

    while (c_isspace(*cur) || *cur == '\\')
        cur++;
    *str = cur;
}

/**
 * virTrimSpaces:
 * @str: string to modify to remove all trailing spaces
 * @endp: track the end of the string
 *
 * If @endp is NULL on entry, then all spaces prior to the trailing
 * NUL in @str are removed, by writing NUL into the appropriate
 * location.  If @endp is non-NULL but points to a NULL pointer,
 * then all spaces prior to the trailing NUL in @str are removed,
 * NUL is written to the new string end, and endp is set to the
 * location of the (new) string end.  If @endp is non-NULL and
 * points to a non-NULL pointer, then that pointer is used as
 * the end of the string, endp is set to the (new) location, but
 * no NUL pointer is written into the string.
 */
void
virTrimSpaces(char *str, char **endp)
{
    char *end;

    if (!endp || !*endp)
        end = str + strlen(str);
    else
        end = *endp;
    while (end > str && c_isspace(end[-1]))
        end--;
    if (endp) {
        if (!*endp)
            *end = '\0';
        *endp = end;
    } else {
        *end = '\0';
    }
}

/**
 * virSkipSpacesBackwards:
 * @str: start of string
 * @endp: on entry, *endp must be NULL or a location within @str, on exit,
 * will be adjusted to skip trailing spaces, or to NULL if @str had nothing
 * but spaces.
 */
void
virSkipSpacesBackwards(const char *str, char **endp)
{
    /* Casting away const is safe, since virTrimSpaces does not
     * modify string with this particular usage.  */
    char *s = (char*) str;

    if (!*endp)
        *endp = s + strlen(s);
    virTrimSpaces(s, endp);
    if (s == *endp)
        *endp = NULL;
}

char *
virArgvToString(const char *const *argv)
{
    int len;
    size_t i;
    char *ret, *p;

    for (len = 1, i = 0; argv[i]; i++)
        len += strlen(argv[i]) + 1;

    if (VIR_ALLOC_N(ret, len) < 0)
        return NULL;
    p = ret;

    for (i = 0; argv[i]; i++) {
        if (i != 0)
            *(p++) = ' ';

        strcpy(p, argv[i]);
        p += strlen(argv[i]);
    }

    *p = '\0';

    return ret;
}

/**
 * virStrdup:
 * @dest: where to store duplicated string
 * @src: the source string to duplicate
 * @report: whether to report OOM error, if there is one
 * @domcode: error domain code
 * @filename: caller's filename
 * @funcname: caller's funcname
 * @linenr: caller's line number
 *
 * Wrapper over strdup, which reports OOM error if told so,
 * in which case callers wants to pass @domcode, @filename,
 * @funcname and @linenr which should represent location in
 * caller's body where virStrdup is called from. Consider
 * using VIR_STRDUP which sets these automatically.
 *
 * Returns: 0 for NULL src, 1 on successful copy, -1 otherwise.
 */
int
virStrdup(char **dest,
          const char *src,
          bool report,
          int domcode,
          const char *filename,
          const char *funcname,
          size_t linenr)
{
    *dest = NULL;
    if (!src)
        return 0;
    if (!(*dest = strdup(src))) {
        if (report)
            virReportOOMErrorFull(domcode, filename, funcname, linenr);
        return -1;
    }

    return 1;
}

/**
 * virStrndup:
 * @dest: where to store duplicated string
 * @src: the source string to duplicate
 * @n: how many bytes to copy
 * @report: whether to report OOM error, if there is one
 * @domcode: error domain code
 * @filename: caller's filename
 * @funcname: caller's funcname
 * @linenr: caller's line number
 *
 * Wrapper over strndup, which reports OOM error if told so,
 * in which case callers wants to pass @domcode, @filename,
 * @funcname and @linenr which should represent location in
 * caller's body where virStrndup is called from. Consider
 * using VIR_STRNDUP which sets these automatically.
 *
 * In case @n is smaller than zero, the whole @src string is
 * copied.
 *
 * Returns: 0 for NULL src, 1 on successful copy, -1 otherwise.
 */
int
virStrndup(char **dest,
           const char *src,
           ssize_t n,
           bool report,
           int domcode,
           const char *filename,
           const char *funcname,
           size_t linenr)
{
    *dest = NULL;
    if (!src)
        return 0;
    if (n < 0)
        n = strlen(src);
    if (!(*dest = strndup(src, n))) {
        if (report)
            virReportOOMErrorFull(domcode, filename, funcname, linenr);
        return -1;
    }

   return 1;
}


size_t virStringListLength(char **strings)
{
    size_t i = 0;

    while (strings && strings[i])
        i++;

    return i;
}
