--- BEGIN_PIN_INFO ---

--- X1 in ---
--- X2 in ---
--- Z3 hang ---
--- X4 in ---
--- X5 in ---
--- Y6 out ---
--- GND7 gnd ---
--- Y8 out ---
--- X9 in ---
--- X10 in ---
--- Z11 hang ---
--- X12 in ---
--- X13 in ---
--- VCC14 vcc ---

--- END_PIN_INFO ---

--- BEGIN_CODE ---

LIBRARY IEEE ; 
USE IEEE.STD_LOGIC_1164.ALL ; 
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL ; 

entity MOD_74LS20 is
--- BEGIN_PORT_DEF ---
port(
    X1, X2, X4, X5, X9, X10, X12, X13: in std_logic;
    Y6, Y8: out std_logic
);
--- END_PORT_DEF ---
end MOD_74LS20;

architecture MOD_74LS20_behv of MOD_74LS20 is

component NAND_GATE4 
port(
    a, b, c, d: in std_logic;
    f: out std_logic
    );
end component;

begin

    u1: NAND_GATE4 port map(a => X1, b => X2, c => X4, d => X5, f => Y6);
    u2: NAND_GATE4 port map(a => X9, b => X10, c => X12, d => X13, f => Y8);

end MOD_74LS20_behv;

--- END_CODE ---
