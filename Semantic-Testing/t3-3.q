(* dangling ELSE binds to closest IF *)

def main( input, output );
  var a: integral;

begin
  read(a);
  if ( a < 10 ) then
    if ( a >= 10 ) then
      a := 1
  else
      a := 0;
  write(a)
end.

