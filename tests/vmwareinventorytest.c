/*
 * Copyright (c) 2013. Doug Goldstein <cardoe@cardoe.com>
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
 */

#include <config.h>

#include "testutils.h"

#ifdef WITH_VMWARE

# include <stdio.h>
# include <stdlib.h>

# include "vmware/vmware_conf.h"

//# define VIR_FROM_THIS VIR_FROM_NONE

struct testInfo {
    const char *in;
    const char *out;
};

static int
testInventoryParse(const void *data)
{
    const struct testInfo *info = data;
    int ret = -1;
    char *path = NULL;
    char *input = NULL;
    char *output = NULL;
    char **parsed_configs = NULL;
    char **test_configs = NULL;
    size_t x;

    if (virAsprintf(&path, "%s/vmwareinventorydata/%s.inventory", abs_srcdir,
                    info->in) < 0)
        return -1;

    if (virtTestLoadFile(path, &input) < 0)
        goto cleanup;

    VIR_FREE(path);

    if (virAsprintf(&path, "%s/vmwareinventorydata/%s.expected", abs_srcdir,
                    info->out) < 0)
        goto cleanup;

    if (virtTestLoadFile(path, &output) < 0)
        goto cleanup;

    if (vmwareParseInventory(input, strlen(input), &parsed_configs) < 0) {
        fprintf(stderr, "Failed to parse VMX configs from inventory file\n");
        goto cleanup;
    }

    if ((test_configs = virStringSplit(output, "\n", 0)) == NULL)
        goto cleanup;

    for (x = 0; parsed_configs[x] && test_configs[x]; x++) {
        if (STRNEQ(parsed_configs[x], test_configs[x])) {
            fprintf(stderr, "vmx %zu differed. Expected: %s, Got: %s\n",
                    x, test_configs[x], parsed_configs[x]);
            goto cleanup;
        }
    }

    /* These should be NULL */
    if (parsed_configs[x]) {
        fprintf(stderr, "More VMX entries found than expected. Found: %zu\n",
                x);
        goto cleanup;
    }

    if (test_configs[x] && test_configs[x][0]) {
        fprintf(stderr, "Less VMX entries found than expected. Only had: %zu\n",
                x);
        goto cleanup;
    }

    ret = 0;

cleanup:
    VIR_FREE(parsed_configs);
    VIR_FREE(test_configs);
    VIR_FREE(path);
    VIR_FREE(input);
    VIR_FREE(output);
    return ret;
}

static int
mymain(void)
{
    int ret = 0;

# define DO_TEST(_in, _out)                                             \
    do {                                                                \
        struct testInfo info = {                                        \
            _in, _out                                                   \
        };                                                              \
        if (virtTestRun("VMware Inventory Parsing " _in,                \
                        testInventoryParse, &info) < 0)                 \
            ret = -1;                                                   \
    } while (0)

    DO_TEST("single-machine", "single-machine");
    DO_TEST("fusion-example-1", "fusion-example-1");
    DO_TEST("workstation-example-1", "workstation-example-1");

    return ret == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

VIRT_TEST_MAIN(mymain)

#else

int
main(void)
{
    return EXIT_AM_SKIP;
}

#endif /* WITH_VMWARE */
