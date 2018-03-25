#include <sys/resource.h>
#include <sys/wait.h>
#include "dash.h"
#include "redirect.h"

using namespace std;

Redirect::Redirect(string _command) : command(_command) {}

