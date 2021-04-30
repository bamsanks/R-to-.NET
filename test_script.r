# TODO: Set this path!
dllPath <- "/path/to/Tunnel.dll"

dyn.load(dllPath)

op1 = 3L
op2 = 4L
result = 0L
success = FALSE
message = ""

.C("Multiply", op1, op2, result, success, message)

dyn.unload(dllPath)
