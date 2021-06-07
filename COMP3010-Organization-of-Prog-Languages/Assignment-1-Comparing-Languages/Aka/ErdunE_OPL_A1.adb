with Ada.Text_IO; use Ada.Text_IO;


procedure ass1 is
    type MatrixType is array (Positive range <>, Positive range <>) of Integer;
    matrix : MatrixType := ((1, 2, 3), (4, 5, 6), (7, 8, 9));
    height : Integer := matrix'Length(1);
    width : Integer := matrix'Length(2);
    ans_number: Integer := width**height;
    type AnsType is array (1..ans_number, 1..Height) of Integer;
    
    function Cartesian(A: MatrixType) return AnsType is
        ans : AnsType;
        interval_width: integer;
        interval_number: integer;
        interval_offset: integer;
        start: integer;
    begin
        for j in 1..height loop
            interval_width := width**(height - j);
            interval_number := width**(j - 1);
            for i in 1..width loop
                start := interval_width * (i - 1);
                for n in 1..interval_number loop
                    interval_offset := (n-1)*interval_width*width;
                    for xpos in 1..interval_width loop
                        ans (xpos+start+interval_offset, j) :=  A (j, i);
                    end loop;
                end loop;
            end loop;
        end loop;
        return ans;
    end Cartesian;
    res : AnsType := Cartesian(matrix);
    counter : Integer := 0;
begin
    for i in 1..ans_number loop
        counter := counter + 1;
        for j in 1..height loop
            Put (Integer'Image (res (i, j)));
        end loop;
        New_Line;
    end loop;
    Put ("total: " & Integer'Image (counter));
end ass1;
