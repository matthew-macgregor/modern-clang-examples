#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sqlite3.h>
#include <string.h>

struct sqlite_ctx {
    sqlite3 *db;
    char *errMsg;
    int returnCode;
};

typedef struct User {
    char *first_name;
    char *last_name;
} User;

typedef struct UserTableResult {
    User        *users;  // Array of contiguous User structs
    char        *errMsg;
    uint32_t    numAlloc; // Count of slots allocated
    uint32_t    numFilled; // Slots filled in users[]
    uint32_t    allocSzBytes; // Bytes allocated 
    int         returnCode;
} UserTableResult;

void cleanup_user_tab(UserTableResult *user_tab)
{
    for (uint32_t i = 0; i < user_tab->numFilled; ++i)
    {
        User u = user_tab->users[i];
        sqlite3_free(u.first_name);
        u.first_name = NULL;
        sqlite3_free(u.last_name);
        u.last_name = NULL;
    }

    free(user_tab->users);
}

int init_user_tab(UserTableResult *user_tab)
{
    // Allocate initial memory for a block of ten rows of Users
    const int init_rows = 10; 
    size_t user_sz_bytes = init_rows * sizeof(User**);
    user_tab->numAlloc = init_rows;
    user_tab->numFilled = 0;
    user_tab->allocSzBytes = user_sz_bytes;
    user_tab->users = malloc(user_sz_bytes * init_rows);
    user_tab->returnCode = user_tab->users ? SQLITE_OK : SQLITE_NOMEM;
    return user_tab->returnCode;
}

static int callback(void *pArg, int argc, char **argv, char **colName)
{
    char *str;
    UserTableResult *tab = (UserTableResult*) pArg;
    if (tab->numFilled == tab->numAlloc)
    {
        // TODO: Realloc if we're out of alloc'd memory
        tab->errMsg = sqlite3_mprintf("All allocated memory is full.\n");
        return SQLITE_NOMEM;
    }

    User *user = &tab->users[tab->numFilled];
    user->last_name = NULL;
    user->first_name = NULL;
    for (int i = 0; i < argc; i++)
	{
        str = sqlite3_mprintf("%s", argv[i]);
        if (strcmp(colName[i], "FirstName") == 0) {
            user->first_name = str;
        } else if (strcmp(colName[i], "LastName") == 0) {
            user->last_name = str;
        }
	}
    tab->numFilled++;
	return SQLITE_OK;
}

int main(int argc, char *argv[]) 
{
    puts("Arguments:");
    for (int i = 0; i < argc; i++)
    {
        printf("%d - %s\n", i, argv[i]);
    }

    printf("SQLite3 Version: %s\n", sqlite3_libversion());

    // Initialize sqlite context struct
    struct sqlite_ctx ctx;
    ctx.db = NULL;
    ctx.errMsg = 0;
    ctx.returnCode = 0;

    char *stmts[] = {
        "CREATE TABLE IF NOT EXISTS Users (FirstName varchar(30), LastName varchar(30))",
        "INSERT INTO Users (FirstName, LastName) VALUES ('Matthew', 'MacGregor')",
        "INSERT INTO Users (FirstName, LastName) VALUES ('Pussycat', 'Larue')",
        "SELECT * FROM Users",
        "DELETE FROM Users",
        "DROP TABLE Users"
    };

    ctx.returnCode = sqlite3_open("Users.db", &ctx.db);
    if (ctx.returnCode == SQLITE_OK)
    {
        puts("Opened database");
        size_t arr_len = sizeof(stmts) / sizeof(stmts[0]);

        // Allocate space for our users collection
        UserTableResult tab;
        if (init_user_tab(&tab) != SQLITE_OK)
        {
            puts("Critical failure to allocate memory");
            exit(42);
        }

        for (unsigned int i = 0; i < arr_len; i++)
        {
            char *stmt = stmts[i];
            printf("Executing Statement: %s\n", stmt);
            ctx.returnCode = sqlite3_exec(ctx.db, stmt, callback, &tab, &ctx.errMsg);
            if (ctx.errMsg != NULL)
            {
                printf("An Error Occurred: %s \n", ctx.errMsg);
                sqlite3_free(ctx.errMsg);
                ctx.errMsg = NULL;
                exit(ctx.returnCode);
            }
        }

        for (unsigned int i = 0; i < tab.numFilled; i++)
        {
            User u = tab.users[i];
            const char *fn = u.first_name ? u.first_name : "<null>";
            const char *ln = u.last_name ? u.last_name : "<null>";
            printf("FirstName: %s, LastName: %s\n", fn, ln);
        }

        cleanup_user_tab(&tab);
        sqlite3_close(ctx.db);
        puts("Closed Database");
    }
    else
    {
        printf("Failed to open database: %s\n", sqlite3_errmsg(ctx.db));
        return ctx.returnCode;
    }
}