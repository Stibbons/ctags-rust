/***************************************************************************
 * rust.c
 * Rust module for ctags
 **************************************************************************/

/* INCLUDE FILES */
#include "general.h"
#include "parse.h"
#include "read.h"

/* DATA DEFINITIONS */
typedef enum eRustKinds {
    K_FUNCTIONS,
    K_TYPES,
    K_ENUMS,
    K_STRUCTS,
    K_MODULES,
    K_STATICS,
    K_TRAITS,
    K_IMPLS,
    K_MACROS,
} RustKind;

static kindOption RustKinds [] = {
    { TRUE, 'f', "functions", "functions" },
    { FALSE, 'T', "types", "types" },
    { FALSE, 'T', "enums", "enumerations" },
    { FALSE, 'm', "struct", "structures" },
    { FALSE, 'm', "mod", "modules" },
    { FALSE, 'm', "const", "constants" },
    { FALSE, 'm', "statics", "statics" },
    { FALSE, 'm', "traits", "traits" },
    { FALSE, 'm', "impl", "implementation" },
    { FALSE, 'm', "macro", "macro rules" },
};

/* FUNCTION DEFINITIONS */

static void functions (const char *const line, const regexMatch *const matches,
                       const unsigned int count)
{
    if (count > 1)    /* should always be true per regex */
    {
        vString *const name = vStringNew ();
        vStringNCopyS (name, line + matches [1].start, matches [1].length);
        makeSimpleTag (name, RustKinds, K_DEFINE);
    }
}

static void findRustTags (void)
{
    while (fileReadLine () != NULL)
        ;  /* don't need to do anything here since callback is sufficient */
}

static void installRust (const langType language)
{
    addCallbackRegex (language, "\\s*fn\\s+([a-zA-Z0-9_,\\s]+)", NULL, functions);

    // --regex-rust=/[ \t]*type[ \t]+([a-zA-Z0-9_]+)/\1/T,types/
    // addCallbackRegex (language, "^def[ \t]+([a-zA-Z0-9_]+)", NULL, types);

    // --regex-rust=/[ \t]*enum[ \t]+([a-zA-Z0-9_]+)/\1/T,types/
    // addCallbackRegex (language, "^def[ \t]+([a-zA-Z0-9_]+)", NULL, types);

    // --regex-rust=/[ \t]*struct[ \t]+([a-zA-Z0-9_]+)/\1/m,types/
    // addCallbackRegex (language, "^def[ \t]+([a-zA-Z0-9_]+)", NULL, types);

    // --regex-rust=/[ \t]*mod[ \t]+([a-zA-Z0-9_]+)/\1/m,modules/
    // addCallbackRegex (language, "^def[ \t]+([a-zA-Z0-9_]+)", NULL, types);

    // --regex-rust=/[ \t]*static[ \t]+([a-zA-Z0-9_]+)/\1/m,consts/
    // addCallbackRegex (language, "^def[ \t]+([a-zA-Z0-9_]+)", NULL, types);

    // --regex-rust=/[ \t]*trait[ \t]+([a-zA-Z0-9_]+)/\1/m,traits/
    // addCallbackRegex (language, "^def[ \t]+([a-zA-Z0-9_]+)", NULL, types);

    // --regex-rust=/[ \t]*impl[ \t]+([a-zA-Z0-9_]+)/\1/m,impls/
    // addCallbackRegex (language, "^def[ \t]+([a-zA-Z0-9_]+)", NULL, types);

    // --regex-rust=/[ \t]*macro_rules![ \t]+([a-zA-Z0-9_]+)/\1/m,macros/
    // addCallbackRegex (language, "^def[ \t]+([a-zA-Z0-9_]+)", NULL, types);
}

/* Create parser definition stucture */
extern parserDefinition* RustParser (void)
{
    static const char *const extensions [] = { "rs", NULL };
    parserDefinition* def = parserNew ("Rust");
    def->kinds      = RustKinds;
    def->kindCount  = KIND_COUNT (RustKinds);
    def->extensions = extensions;
    def->parser     = findRustTags;
    def->initialize = installRust;
    return def;
}
