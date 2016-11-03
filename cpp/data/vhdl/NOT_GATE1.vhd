--- BEGIN_PIN_INFO ---
--- X in ---
--- F1 out ---
--- END_PIN_INFO ---

--- BEGIN_CODE ---

LIBRARY IEEE ; 
USE IEEE.STD_LOGIC_1164.ALL ; 
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL ; 


entity NOT_GATE1 is
--- BEGIN_PORT_DEF ---
port(
    X: in std_logic;
    F1: out std_logic
);
--- END_PORT_DEF ---
end NOT_GATE1;

architecture NOT_GATE1_behv of NOT_GATE1 is
begin
    F1 <= not(X);
end NOT_GATE1_behv;

--- END_CODE ---