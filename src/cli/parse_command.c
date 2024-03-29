// base
#include <base/alloc.h>
#include <base/format.h>
#include <base/new.h>
// cli
#include <cli/emit.h>
#include <cli/help.h>
#include <cli/parse_command.h>
#include <cli/version.h>
// c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// static functions
static void help();
static void version();
static void error(const ParseCommand* self);

CONSTRUCTOR(
    ParseCommand,
    ParseCommand,
    const char* command,
    const char** options,
    const Usize options_size
) {

    enum Command command_kind;
    // copy of command
    char* cmd;
    strcpy(cmd, command);
    // convert command to lowercase
    for (int i = 0; cmd[i]; i++) {
        cmd[i] = tolower(cmd[i]);
    }

    if (!(strcmp(cmd, "build")))
        command_kind = COMMAND_BUILD;
    else if (!(strcmp(cmd, "cc")))
        command_kind = COMMAND_CC;
    else if (!(strcmp(cmd, "compile")))
        command_kind = COMMAND_COMPILE;
    else if (!(strcmp(cmd, "cpp")))
        command_kind = COMMAND_CPP;
    else if (!(strcmp(cmd, "init")))
        command_kind = COMMAND_INIT;
    else if (!(strcmp(cmd, "install")))
        command_kind = COMMAND_INSTALL;
    else if (!(strcmp(cmd, "new")))
        command_kind = COMMAND_NEW;
    else if (!(strcmp(cmd, "run")))
        command_kind = COMMAND_RUN;
    else if (!(strcmp(cmd, "test")))
        command_kind = COMMAND_TEST;
    else if (!(strcmp(cmd, "to")))
        command_kind = COMMAND_TO;
    else if (!(strcmp(cmd, "version")))
        command_kind = COMMAND_VERSION;
    else command_kind = COMMAND_ERROR;

    return (ParseCommand) {
        .command = cmd,
        .options = options,
        .options_size = options_size,
        .command_kind = command_kind,
    };
}

#define PARSE_COMMAND(option_type, parse, l_name, u_name)                      \
    static Option parse_##l_name##__ParseCommand(const ParseCommand* self)     \
    {                                                                          \
        if (self->options_size == 0) {                                         \
            puts(u_name##_HELP);                                               \
            exit(0);                                                           \
        } else {                                                               \
            Vec* options = parse(self->options, self->options_size);           \
            for (Usize i = 0; i < options->len; i++) {                         \
                option_type op = get__Vec(options, i);                         \
                switch (op->kind) {                                            \
                    case u_name##_OPTION_KIND_ERROR: {                         \
                        char* msg = format("unknown option `{s}`", op->error); \
                        EMIT_ERROR(msg);                                       \
                        glang_free(msg);                                       \
                        break;                                                 \
                    }                                                          \
                    case u_name##_OPTION_KIND_HELP:                            \
                        puts(u_name##_HELP);                                   \
                        exit(0);                                               \
                        break;                                                 \
                    default:                                                   \
                        break;                                                 \
                }                                                              \
            }                                                                  \
            return NEW_VARIANT(Option, l_name, options);                       \
        }                                                                      \
    }

PARSE_COMMAND(BuildOption*, parse__BuildOption, build, BUILD);
PARSE_COMMAND(CompileOption*, parse__CompileOption, compile, COMPILE);
PARSE_COMMAND(InitOption*, parse__InitOption, init, INIT);
PARSE_COMMAND(InstallOption*, parse__InstallOption, install, INSTALL);
PARSE_COMMAND(RunOption*, parse__RunOption, run, RUN);


void help() {
    puts(DEFAULT_HELP);
    exit(0);
}
void version() {
    printf("%s\n", GLANG_VERSION);
    exit(0);
}
void error(const ParseCommand* self) {

    char* msg = format("unknown command `{s}`", self->command);

    EMIT_ERROR(msg);

    glang_free(msg);
    exit(1);
}

Option run__ParseCommand(const ParseCommand* self) {

    switch (self->command_kind) {
        case COMMAND_BUILD:
            return parse_build__ParseCommand(self);
        case COMMAND_COMPILE:
            return parse_compile__ParseCommand(self);
        case COMMAND_INIT:
            return parse_init__ParseCommand(self);
        case COMMAND_INSTALL:
            return parse_install__ParseCommand(self);
        case COMMAND_RUN:
            return parse_run__ParseCommand(self);
        case COMMAND_VERSION:
            version();
        case COMMAND_ERROR:
            error(self);
    }

}
