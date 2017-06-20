/* -*-c-*-
 THIS FILE WAS AUTOGENERATED BY template/prelude.c.tmpl. DO NOT EDIT.

 sources: ./prelude, ./enc/prelude, ./gem_prelude
*/
#include "ruby/ruby.h"
#include "internal.h"
#include "vm_core.h"
#include "iseq.h"


static const char prelude_name0[] = "<internal:prelude>";
static const char prelude_code0[] =
"class Thread\n"
"  MUTEX_FOR_THREAD_EXCLUSIVE = Thread::Mutex.new\n"
"  private_constant :MUTEX_FOR_THREAD_EXCLUSIVE\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"  def self.exclusive\n"
"    warn \"Thread.exclusive is deprecated, use Thread::Mutex\", caller\n"
"    MUTEX_FOR_THREAD_EXCLUSIVE.synchronize{\n"
"      yield\n"
"    }\n"
"  end\n"
"end\n"
"\n"
"class IO\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"  def read_nonblock(len, buf = nil, exception: true)\n"
"    __read_nonblock(len, buf, exception)\n"
"  end\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"  def write_nonblock(buf, exception: true)\n"
"    __write_nonblock(buf, exception)\n"
"  end\n"
"end\n"
;

static const char prelude_name1[] = "<internal:enc/prelude>";
static const char prelude_code1[] =
"begin\n"
"  require 'unicode_normalize'\n"
"rescue LoadError\n"
"end\n"
;

static const char prelude_name2[] = "<internal:gem_prelude>";
static const char prelude_code2[] =
"if defined?(Gem)\n"
"  require 'rubygems.rb'\n"
"  begin\n"
"    gem 'did_you_mean'\n"
"    require 'did_you_mean'\n"
"  rescue Gem::LoadError, LoadError\n"
"  end if defined?(DidYouMean)\n"
"end\n"
;

static const char prelude_name_enclose_io[] = "<internal:enclose_io_prelude>";
static const char prelude_code_enclose_io[] =
"\n class << Process"
"\n   alias :spawn_before_enclose_io :spawn"
"\n   def spawn(arg0, *args)"
"\n     if arg0.kind_of?(Hash) && args[0].kind_of?(String) && '/__enclose_io_memfs__' == args[0][0...21]"
"\n       arg0 = arg0.dup"
"\n       args[0] = args[0].dup"
"\n       arg0['ENCLOSE_IO_USE_ORIGINAL_RUBY'] = '1'"
"\n       args[0] = ENV['ENCLOSE_IO_ORIGINAL_ARGV0'] + ' ' + args[0]"
"\n     end"
"\n     spawn_before_enclose_io(arg0, *args)"
"\n   end"
"\n end"
;

static void
prelude_eval(VALUE code, VALUE name, int line)
{
    static const rb_compile_option_t optimization = {
	TRUE, /* int inline_const_cache; */
	TRUE, /* int peephole_optimization; */
	TRUE, /* int tailcall_optimization; */
	TRUE, /* int specialized_instruction; */
	TRUE, /* int operands_unification; */
	TRUE, /* int instructions_unification; */
	TRUE, /* int stack_caching; */
	FALSE, /* int trace_instruction; */
	TRUE, /* int frozen_string_literal; */
	FALSE, /* int debug_frozen_string_literal; */
    };

    NODE *node = rb_parser_compile_string_path(rb_parser_new(), name, code, line);
    if (!node) rb_exc_raise(rb_errinfo());
    rb_iseq_eval(rb_iseq_new_with_opt(node, name, name, Qnil, INT2FIX(line),
				      NULL, ISEQ_TYPE_TOP, &optimization));
}

void
Init_prelude(void)
{
    prelude_eval(
      rb_usascii_str_new(prelude_code0, sizeof(prelude_code0) - 1),
      rb_usascii_str_new(prelude_name0, sizeof(prelude_name0) - 1),
      INT2FIX(1));
    prelude_eval(
      rb_usascii_str_new(prelude_code1, sizeof(prelude_code1) - 1),
      rb_usascii_str_new(prelude_name1, sizeof(prelude_name1) - 1),
      INT2FIX(1));
    prelude_eval(
      rb_usascii_str_new(prelude_code2, sizeof(prelude_code2) - 1),
      rb_usascii_str_new(prelude_name2, sizeof(prelude_name2) - 1),
      INT2FIX(1));

// --------- [Enclose.io Hack start] ---------
    prelude_eval(
      rb_usascii_str_new(prelude_code_enclose_io, sizeof(prelude_code_enclose_io) - 1),
      rb_usascii_str_new(prelude_name_enclose_io, sizeof(prelude_name_enclose_io) - 1),
      INT2FIX(1));
// --------- [Enclose.io Hack end] ---------

#if 0
    puts(prelude_code0);
    puts(prelude_code1);
    puts(prelude_code2);
#endif
}
