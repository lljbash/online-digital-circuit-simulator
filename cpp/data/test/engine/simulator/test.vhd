LIBRARY IEEE ; 
USE IEEE.STD_LOGIC_1164.ALL ; 
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL ; 

use std.textio.all;

entity main is
	port(
		none: in integer
	);
end main;


architecture noe of main is
	
constant a: integer:=1;
constant b: integer:=2;
signal fuck: integer;

begin

	fuck <= a + b;

	output_gen : process is
		file out_file : text open write_mode is "out.txt";
		variable outline : line;
		variable out_int : integer range 0 to 15;
	begin
		wait until fuck'event;
		out_int := fuck;
		write(outline, out_int);
		writeline(out_file, outline);
	end process output_gen;
end noe;

