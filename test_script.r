# TODO: Set this path!
dllPath <- "/path/to/Tunnel.dll"

dyn.load(dllPath)

ret <- .C("Multiply",
  op1 = 3L,
  op2 = 4L,
  result = 0L,
  success = FALSE,
  message = "")

if (ret$success) cat(ret$result)

dyn.unload(dllPath)
