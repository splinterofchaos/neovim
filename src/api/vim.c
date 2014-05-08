#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "api/vim.h"
#include "api/helpers.h"
#include "api/defs.h"
#include "api/buffer.h"
#include "../vim.h"
#include "types.h"
#include "ascii.h"
#include "ex_docmd.h"
#include "screen.h"
#include "memory.h"
#include "eval.h"
#include "misc2.h"

void vim_push_keys(String str)
{
  abort();
}

void vim_command(String str, Error *err)
{
  // We still use 0-terminated strings, so we must convert.
  char cmd_str[str.size + 1];
  memcpy(cmd_str, str.data, str.size);
  cmd_str[str.size] = NUL;
  // Run the command
  try_start();
  do_cmdline_cmd((char_u *)cmd_str);
  update_screen(VALID);
  try_end(err);
}

Object vim_eval(String str, Error *err)
{
  Object rv;

  char expr_str[str.size + 1];
  memcpy(expr_str, str.data, str.size);
  expr_str[str.size] = NUL;
  // Evaluate the expression
  try_start();
  typval_T *expr_result = eval_expr((char_u *)expr_str, NULL);

  if (!try_end(err)) {
    // No errors, convert the result
    rv = vim_to_object(expr_result);
  }

  // Free the vim object
  free_tv(expr_result);
  return rv;
}

int64_t vim_strwidth(String str)
{
  return mb_string2cells((char_u *)str.data, str.size);
}

StringArray vim_list_runtime_paths(void)
{
  StringArray rv = {.size = 0};
  uint8_t *rtp = p_rtp;

  if (*rtp == NUL) {
    // No paths
    return rv;
  }

  // Count the number of paths in rtp
  while (*rtp != NUL) {
    if (*rtp == ',') {
      rv.size++;
    }
    rtp++;
  }

  // index
  uint32_t i = 0;
  // Allocate memory for the copies
  rv.items = xmalloc(sizeof(String) * rv.size);
  // reset the position
  rtp = p_rtp;
  // Start copying
  while (*rtp != NUL) {
    rv.items[i].data = xmalloc(MAXPATHL);
    // Copy the path from 'runtimepath' to rv.items[i]
    rv.items[i].size = copy_option_part(&rtp,
                                       (char_u *)rv.items[i].data,
                                       MAXPATHL,
                                       ",");
    i++;
  }

  return rv;
}

void vim_change_directory(String dir, Error *err)
{
  char string[dir.size + 1];
  memcpy(string, dir.data, dir.size);
  string[dir.size] = NUL;

  try_start();

  if (vim_chdir((char_u *)string)) {
    if (!try_end(err)) {
      set_api_error("failed to change directory", err);
    }
    return;
  }

  post_chdir(FALSE);
  try_end(err);
}

String vim_get_current_line(Error *err)
{
  return buffer_get_line(curbuf->b_fnum, curwin->w_cursor.lnum - 1, err);
}

void vim_set_current_line(Object line, Error *err)
{
  buffer_set_line(curbuf->b_fnum, curwin->w_cursor.lnum - 1, line, err);
}

Object vim_get_var(bool special, String name, Error *err)
{
  abort();
}

void vim_set_var(bool special, String name, Object value, Error *err)
{
  abort();
}

String vim_get_option(String name, Error *err)
{
  abort();
}

void vim_set_option(String name, String value, Error *err)
{
  abort();
}

void vim_del_option(String name, Error *err)
{
  abort();
}

void vim_out_write(String str)
{
  abort();
}

void vim_err_write(String str)
{
  abort();
}

int64_t vim_get_buffer_count(void)
{
  abort();
}

Buffer vim_get_buffer(int64_t num, Error *err)
{
  abort();
}

Buffer vim_get_current_buffer(void)
{
  abort();
}

void vim_set_current_buffer(Buffer buffer)
{
  abort();
}

int64_t vim_get_window_count(void)
{
  abort();
}

Window vim_get_window(int64_t num, Error *err)
{
  abort();
}

Window vim_get_current_window(void)
{
  abort();
}

void vim_set_current_window(Window window)
{
  abort();
}

int64_t vim_get_tabpage_count(void)
{
  abort();
}

Tabpage vim_get_tabpage(int64_t num, Error *err)
{
  abort();
}

Tabpage vim_get_current_tabpage(void)
{
  abort();
}

void vim_set_current_tabpage(Tabpage tabpage)
{
  abort();
}