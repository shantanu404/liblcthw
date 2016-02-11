#include <lcthw/tstree.h>
#include <lcthw/bstrlib.h>

TSTree *add_route_data(TSTree *routes, bstring line)
{
	struct bstrList *data = bsplit(line, ' ');
	check(data->qty == 2, "Line '%s' doesn't have 2 collumns", bdata(line));

	routes = TSTree_insert(routes,
			bdata(data->entry[0]),
			blength(data->entry[0]),
			bstrcpy(data->entry[1]));
	
	bstrListDestroy(data);
	return routes;

error:
	return NULL;
}

TSTree *load_routes(const char* filename)
{
	TSTree *routes = NULL;
	bstring line = NULL;
	FILE *routes_map = NULL;

	routes_map = fopen(filename, "r");
	check(routes_map != NULL, "Failed to open routes: %s", filename);

	while((line = bgets((bNgetc)fgetc, routes_map, '\n')) != NULL) {
		check(btrimws(line) == BSTR_OK, "Failed to trim line.");
		routes = add_route_data(routes, line);
		check(routes != NULL, "Failed to add route.");
		bdestroy(line);
	}
	
	fclose(routes_map);
	return routes;

error:
	if(routes_map) fclose(routes_map);
	if(line) bdestroy(line);
	return NULL;
}

bstring read_line(const char *prompt)
{
	printf("%s", prompt);
	bstring result = bgets((bNgetc)fgetc, stdin, '\n');
    check_debug(result != NULL, "stdin closed.");

    check(btrimws(result) == BSTR_OK, "Failed to trim.");

    return result;

error:
    return NULL;
}

bstring match_url(TSTree *routes, bstring url)
{
	bstring route = TSTree_search(routes, bdata(url), blength(url));

    if(route == NULL) {
        printf("No exact match found, trying prefix.\n");
        route = TSTree_search_prefix(routes, bdata(url), blength(url));
    }

    return route;
}

void bdestroy_cb(void *value, void *ignored)
{
	(void)ignored;
	bdestroy((bstring)value);
}
void destroy_routes(TSTree *routes)
{
	TSTree_traverse(routes, bdestroy_cb, NULL);
	TSTree_destroy(routes);
}

int main(int argc, char *argv[])
{
	bstring url = NULL;
	bstring route = NULL;
	check(argc == 2, "USAGE: urlor <urlfile>");
	
	TSTree *routes = load_routes(argv[1]);
	check(routes != NULL, "Your route file has an error.");
	
	while(1) {
		url = read_line("URL> ");
		check_debug(url != NULL, "goodbye.");
		
		route = match_url(routes, url);
		
		if(route) {
			printf("MATCH: %s == %s\n", bdata(url), bdata(route));
		} else {
			printf("FAIL, %s\n", bdata(url));
		}
		
		bdestroy(url);
	}
	
	destroy_routes(routes);
	return 0;

error:
	destroy_routes(routes);
	return 1;
}

