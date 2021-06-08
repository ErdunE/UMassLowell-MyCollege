 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Assembler;

import EnumationData.Mac1Enum;
import Machine.MainMemory;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.Map;


/*! \brief  MAC1 Aseembler Interpreter Class, Assembly level class
 * 
 *  UNDER UPDATES
 *  It will take input Assembly code and bring it to the interpreter.
 *
 */
public class MAC1Assembler {

    ArrayList<String> inputCode = new ArrayList<>();
    HashMap<String, Integer> tag_table = new HashMap<>();
    HashMap<String, String> memory = new LinkedHashMap<>();
    HashMap<String, Integer> alloacted = new HashMap<>();
    ArrayList<memoryAllocation> memory_information = new ArrayList();
    MainMemory m_memory;
    ArrayList memory_mic1 = new ArrayList();

    String fileName = "mac.txt";

    public ArrayList<String> MacCode() {

        return this.inputCode;
    }

    public MAC1Assembler() {

        m_memory = MainMemory.getInstance();
    }

    public ArrayList<Short> getBinaryCode() {
        return InstructionTranslator.getInstance().translate(inputCode);

    }

    private Mac1Enum checkforTag(String[] data, int i) {

        String previous = getElementSafe(data, i - 1);
        String tag = getElementSafe(data, i);
        String next = getElementSafe(data, i + 1);

        if (tag.contains(":")) {
            if (previous == null) {
                if (InstructionTranslator.getInstance().isValid(next)) {
                    return Mac1Enum.NEW_TAG;
                } else {
                    return Mac1Enum.MEMORY;
                }
            } else if (InstructionTranslator.getInstance().isValid(next) && !InstructionTranslator.getInstance().InstructionHasArgument(previous)) {
                return Mac1Enum.NEW_TAG;
            } else if (InstructionTranslator.getInstance().InstructionHasArgument(previous)) {
                return Mac1Enum.REFERENCE;
            } else if (InstructionTranslator.getInstance().isNumeric(next)) {

                return Mac1Enum.MEMORY;
            } else if (next != null && next.contains(":")) {
                int level = this.checkLevel(data, i, 0);
                level = level % 2;
                switch (level) {
                    case 0:
                        return Mac1Enum.REFERENCE;
                    case 1:
                        return Mac1Enum.MEMORY;
                }
            } else if (next == null) {
                return Mac1Enum.REFERENCE;
            } else if (next.contains("\"")) {
                return Mac1Enum.MEMORY;
            }
        } else if (InstructionTranslator.getInstance().isValid(tag)) {
            return Mac1Enum.CODE;
        } else if (InstructionTranslator.getInstance().isNumeric(tag)) {
            if (InstructionTranslator.getInstance().InstructionHasArgument(previous)) {
                return Mac1Enum.HARDCODE_DATA;
            } else if ((InstructionTranslator.getInstance().isNumeric(next) && previous.contains(":"))) {
                return Mac1Enum.ARRAY_DATA_S;
            } else {
                return Mac1Enum.HARDCODE_DATA;
            }

        }
        return Mac1Enum.IDK;
    }

    private int checkLevel(String[] ray, int place, int level) {
        String temp = this.getElementSafe(ray, place);
        if (temp == null) {
            return level;
        }
        if (temp.contains(":")) {
            level++;
            return checkLevel(ray, place - 1, level);

        }
        return level;
    }

    private String getElementSafe(String[] data, int location) {
        try {
            return data[location];
        } catch (Exception ex) {
            return null;
        }
    }

    public void printstring() {
        System.out.println("--------------------- memory");
        for (Map.Entry<String, String> set : this.memory.entrySet()) {
            System.out.println("__" + set.getKey() + "__" + set.getValue() + "__");
        }

        System.out.println("--------------------- allocated TEMP");
        for (Map.Entry<String, Integer> set : this.alloacted.entrySet()) {
            System.out.println("__" + set.getKey() + "__" + set.getValue() + "__");
        }
        System.out.println("------------------ tag");
        for (Map.Entry<String, Integer> set : this.tag_table.entrySet()) {
            System.out.println("__" + set.getKey() + "__" + set.getValue() + "__");
        }

        System.out.println("------------------- code");
        for (String str : this.inputCode) {
            System.out.println(str);
        }
        System.out.println("----------------------- memory");

    }

    public void loadData(String code) {
        //code = code.substring(4);

        String tokens[] = code.split("\\s+");
        int i = 0;
        int linePosition = 0;
        int line = 0;
        while (linePosition < tokens.length) {

            String token = tokens[linePosition];
            Mac1Enum enum_temp = checkforTag(tokens, linePosition);
            System.out.println(enum_temp + "  " + tokens[linePosition]);
            switch (enum_temp) {
                case CODE:
                    i++;
                    break;
                case NEW_TAG:
                    this.tag_table.put(token, i);
                    break;
                case MEMORY:
                    String data_mem = tokens[linePosition + 1];
                    line = StringClass.getInstance().extractString(tokens, linePosition + 1);
                    if (line != -1) {

                        data_mem = StringClass.getInstance().stringBuild(tokens, linePosition + 1, line);
                        linePosition = line;
                        //System.out.println(data_mem);
                    }
                    System.out.println("TOKEN "+token +" DATA "+data_mem);
                    this.memory.put(token, data_mem);
                    break;
                case ARRAY_DATA_S:
                    line = StringClass.getInstance().extractInteger(tokens, linePosition + 1);
                    if (line != -1) {
                        String arrayTag = tokens[linePosition - 1];
                        data_mem = StringClass.getInstance().stringBuild(tokens, linePosition, line);
                        linePosition = line;
                        System.out.println(data_mem);
                        this.memory.put(arrayTag, data_mem);

                    }

                    break;
            }
            linePosition++;
        }
        this.allocateMemory();
        this.rebuildCode(code);
    }

    private void allocateMemory() {

        for (Map.Entry<String, String> map : this.memory.entrySet()) {

            memoryAllocation allocate = new memoryAllocation();
            int position = 0;
            if (map.getValue().contains(":")) {
                position = m_memory.allocatedData((short) 0, false);
                allocate.dataAllocated = false;
            } else {
                if (map.getValue().contains(" ") && !map.getValue().contains("\"")) {
                    String[] tokens = map.getValue().split("\\s+");
                    int count = 0;
                    for (String token : tokens) {
                        if (!token.isEmpty()) {
                            position = m_memory.allocatedData(Short.valueOf(token), false);
                            count++;
                        }
                    }
                    position = position - (count - 1);
                } else {
                    if (map.getValue().contains("\"")) {
                        ArrayList<Short> data = StringClass.getInstance().convertStringToNumbers(map.getValue());
                        int count = 0;
                        for (short ascii : data) {
                            position = m_memory.allocatedData(ascii, true);
                            count++;
                        }
                        position = position - (count - 1);
                    } else {
                        position = m_memory.allocatedData(Short.valueOf(map.getValue()), false);
                    }
                }
            }
            allocate.tag = map.getKey();
            allocate.value = map.getValue();
            allocate.location = position;

            position++;
            this.memory_information.add(allocate);
        }
        this.allocateReferences();
    }

    private memoryAllocation getAllocation(String tag) {
        for (memoryAllocation allocate : this.memory_information) {
            if (allocate.tag.equals(tag)) {
                return allocate;
            }
        }
        return null;
    }

    private void setAllocate() {
        for (memoryAllocation allocate : this.memory_information) {
            this.alloacted.put(allocate.tag, Integer.valueOf(allocate.location));
        }
    }

    private void allocateReferences() {
        for (memoryAllocation allocate : this.memory_information) {
            if (!allocate.dataAllocated) {
                memoryAllocation key_pointer = getAllocation(allocate.value);
                if (key_pointer != null) {
                    allocate.value = String.valueOf(key_pointer.location);
                    m_memory.setDataStructureValue(allocate.location, Short.valueOf(allocate.value));
                    allocate.dataAllocated = true;
                }
            }
        }
        this.setAllocate();
    }

    private boolean rebuildCode(String code) {

        String tokens[] = code.split("\\s+");
        int i = 0;
        for (String token : tokens) {
            Mac1Enum enum_temp = checkforTag(tokens, i);
            switch (enum_temp) {
                case CODE:
                    String code_line = token;
                    String argument;

                    if (InstructionTranslator.getInstance().InstructionHasArgument(token)) {
                        Mac1Enum argumentEnum = checkforTag(tokens, i + 1);
                        argument = tokens[i + 1];
                        switch (argumentEnum) {
                            case HARDCODE_DATA:

                                break;
                            case REFERENCE:
                                if (this.alloacted.containsKey(argument)) {
                                    argument = String.valueOf(this.alloacted.get(argument));
                                } else if (this.tag_table.containsKey(argument)) {
                                    argument = String.valueOf(this.tag_table.get(argument));
                                } else {
                                    System.out.println("ERROR " + argument);
                                }

                                break;
                            case IDK:
                                System.out.println(token + " ------------>>  " + argument);
                                argument = "**BAD**";
                                break;
                            default:
                                throw new AssertionError(argumentEnum.name());

                        }

                        code_line += " " + argument;
                    }
                    this.inputCode.add(code_line);
                    break;
            }
            i++;
        }

        return false;
    }

    class memoryAllocation {

        String tag;
        int location;
        String value;
        boolean dataAllocated = false;
    }
}