#include <string.h>
#include <stdio.h>
#include <cyaml/cyaml.h>

struct context{
  char*  cluster;
  char*  namespace;
  char*  user;
};

struct context_entry{
  char* name;
  struct context context;
};

struct kubeconfig{
  char* current_context;
  struct context_entry* contexts;
  unsigned contexts_count;
};

static const cyaml_schema_field_t context_mapping_schema[] = {
	CYAML_FIELD_STRING_PTR(
		"cluster", CYAML_FLAG_POINTER, struct context, cluster, 0, CYAML_UNLIMITED),
	CYAML_FIELD_STRING_PTR(
		"namespace", CYAML_FLAG_POINTER | CYAML_FLAG_OPTIONAL, struct context, namespace, 0, CYAML_UNLIMITED),
	CYAML_FIELD_STRING_PTR(
		"user", CYAML_FLAG_POINTER, struct context, user, 0, CYAML_UNLIMITED),
	CYAML_FIELD_END
};

static const cyaml_schema_field_t context_entry_mapping_schema[] = {
	CYAML_FIELD_STRING_PTR(
		"name", CYAML_FLAG_POINTER, struct context_entry, name, 0, CYAML_UNLIMITED),
	CYAML_FIELD_MAPPING(
		"context", CYAML_FLAG_POINTER, struct context_entry, context, context_mapping_schema),
	//CYAML_FIELD_IGNORE(
	//	"context", CYAML_FLAG_OPTIONAL),
	CYAML_FIELD_END
};

static const cyaml_schema_value_t context_entry_schema = {
	CYAML_VALUE_MAPPING(
		CYAML_FLAG_DEFAULT, struct context_entry, context_entry_mapping_schema),
};

static const cyaml_schema_field_t top_mapping_schema[] = {
	CYAML_FIELD_IGNORE(
		"apiVersion", CYAML_FLAG_OPTIONAL),
	CYAML_FIELD_STRING_PTR(
		"current-context", CYAML_FLAG_POINTER, struct kubeconfig, current_context, 0, CYAML_UNLIMITED),
	CYAML_FIELD_IGNORE(
		"clusters", CYAML_FLAG_OPTIONAL),
	CYAML_FIELD_IGNORE(
		"kind", CYAML_FLAG_OPTIONAL),
	CYAML_FIELD_IGNORE(
		"users", CYAML_FLAG_OPTIONAL),
	CYAML_FIELD_IGNORE(
		"preferences", CYAML_FLAG_OPTIONAL),
  CYAML_FIELD_SEQUENCE(
    "contexts", CYAML_FLAG_POINTER,
        struct kubeconfig, contexts, &context_entry_schema,
        0, CYAML_UNLIMITED),	
  CYAML_FIELD_END
};


/* CYAML value schema for the top level mapping. */
static const cyaml_schema_value_t top_schema = {
	CYAML_VALUE_MAPPING(
		CYAML_FLAG_POINTER, struct kubeconfig, top_mapping_schema),
};

/* Create our CYAML configuration. */
static const cyaml_config_t config = {
	.log_fn = cyaml_log,            /* Use the default logging function. */
	.mem_fn = cyaml_mem,            /* Use the default memory allocator. */
	.log_level = CYAML_LOG_WARNING, /* Logging errors and warnings only. */
};


struct kubeconfig *k;

int main(int argc, char** argv){
  cyaml_err_t err = cyaml_load_file(argv[1], &config,
      &top_schema, (cyaml_data_t **)&k, NULL);
  if (err != CYAML_OK) {
    printf("%s\n", "Error loading yaml.");
    return 1;
  }

  printf("%s|", k->current_context);
  for(int i=0; i< k->contexts_count; i++){
    if(!strcmp(k->contexts[i].name, k->current_context)){
      if(k->contexts[i].context.namespace != NULL){
        printf("%s", k->contexts[i].context.namespace);
      }
    }
  }

  err = cyaml_free(&config, &top_schema, k, 0);
  if (err != CYAML_OK) {
    /* Handle error */
  }

  return 0;
}
