/*
  Copyright (c) 2010 Fizians SAS. <http://www.fizians.com>
  This file is part of Rozofs.

  Rozofs is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published
  by the Free Software Foundation; either version 3 of the License,
  or (at your option) any later version.

  Rozofs is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see
  <http://www.gnu.org/licenses/>.
 */


#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <libconfig.h>
#include <unistd.h>
#include "rozofs.h"
#include "xmalloc.h"
#include "log.h"
#include "sconfig.h"

#define SLAYOUT	    "layout"
#define SSTORAGES   "storages"
#define SSID	    "sid"
#define SROOT	    "root"


int storage_config_initialize(storage_config_t *s, sid_t sid, const char *root) {
	DEBUG_FUNCTION;

	s->sid = sid;
	memcpy(s->root, root, FILENAME_MAX * sizeof(char));
	list_init(&s->list);
	return 0;
}

void storage_config_release(storage_config_t *s) {
	return;
}

int sconfig_initialize(sconfig_t *sc) {
    DEBUG_FUNCTION;

    list_init(&sc->storages);
    return 0;
}

void sconfig_release(sconfig_t *config) {
	list_t *p, *q;
	DEBUG_FUNCTION;

    list_for_each_forward_safe(p, q, &config->storages) {
        storage_config_t *entry = list_entry(p, storage_config_t, list);
        storage_config_release(entry);
        list_remove(p);
        free(entry);
    }
}

int sconfig_read(sconfig_t *config, const char *fname) {
    int status = -1;
    config_t cfg;
    long int layout;
    struct config_setting_t *settings = 0;
    int i;
    DEBUG_FUNCTION;

    config_init(&cfg);

    if (config_read_file(&cfg, fname) == CONFIG_FALSE) {
        errno = EIO;
        fatal("can't read %s : %s.", fname, config_error_text(&cfg));
        goto out;
    }

    if (!config_lookup_int(&cfg, SLAYOUT, &layout)) {
        errno = ENOKEY;
        fatal("can't fetch layout setting.");
        goto out;
    }
    config->layout = (sid_t)layout;

    if (!(settings = config_lookup(&cfg, SSTORAGES))) {
        errno = ENOKEY;
        fatal("can't fetch storages settings.");
        goto out;
    }

    for (i = 0; i < config_setting_length(settings); i++) {
        storage_config_t *new = 0;
        struct config_setting_t *ms = 0;
        long int sid;
        const char *root = 0;

        if (!(ms = config_setting_get_elem(settings, i))) {
            errno = ENOKEY;
            severe("cant't fetch storage.");
            goto out;
        }

        if (config_setting_lookup_int(ms, SSID, &sid) == CONFIG_FALSE) {
            errno = ENOKEY;
            fatal("cant't lookup sid for storage %d.", i);
            goto out;
        }


        if (config_setting_lookup_string(ms, SROOT, &root) == CONFIG_FALSE) {
            errno = ENOKEY;
            fatal("cant't lookup root path for storage %d.", i);
            goto out;
        }

        new = xmalloc(sizeof(storage_config_t));
        if (storage_config_initialize(new, (sid_t)sid, root) != 0) {
            goto out;
        }
        list_push_back(&config->storages, &new->list);
    }

    status = 0;
out:
    config_destroy(&cfg);
    return status;
}

int sconfig_validate(sconfig_t *config) {
    int status = -1;
    list_t *p;
    DEBUG_FUNCTION;

    if (config->layout < LAYOUT_2_3_4 || config->layout > LAYOUT_8_12_16) {
        severe("unknown layout: %d.", config->layout);
        errno = EINVAL;
        goto out;
    }

    list_for_each_forward(p, &config->storages) {
        list_t *q;
        storage_config_t *e1 = list_entry(p, storage_config_t, list);
        if (access(e1->root, F_OK) != 0) {
            severe("invalid root %s: %s.", e1->root, strerror(errno));
            errno = EINVAL;
            goto out;
        }
        list_for_each_forward(q, &config->storages) {
            storage_config_t *e2 = list_entry(q, storage_config_t, list);
            if (e1 == e2)
                continue;
            if (e1->sid == e2->sid) {
                severe("duplicated sid: %d", e1->sid);
                errno = EINVAL;
                goto out;
            }

            if (strcmp(e1->root, e2->root) == 0) {
                severe("duplicated root: %s", e1->root);
                errno = EINVAL;
                goto out;
            }
        }
    }

    status = 0;
out:
    return status;
}
