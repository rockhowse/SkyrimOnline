from xml.dom.minidom import parse, parseString
import os
import sys

def GetCppType(Type):
    if Type == "float" or Type == "char" or Type == "double":
        return Type
    if Type == "string":
        return 'std::string'
    return Type + '_t'

def GenerateOpcodes(messages, output, origin, destination):
    filepath = os.path.join(output, origin + destination + '_Opcode.h')

    print('Generating opcode header', filepath,'...')
    
    f = open(filepath, 'w')
    f.write('// This file was generated, do not modify it !!!!  \n\n')

    fileDef = ('MSG_'+origin+'_'+destination+'_OPCODE_H\n').upper()
    f.write('#ifndef ' + fileDef)
    f.write('#define ' + fileDef)
    f.write('\n')
    f.write('#if defined(_MSC_VER) && (_MSC_VER >= 1200)\n')
    f.write('# pragma once\n')
    f.write('#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)\n\n')
    f.write('namespace Messages\n{\n')
    f.write('\tenum '+origin+destination+'_Opcodes\n');
    f.write('\t{\n')   
    
    
    for message in messages:
        if message.getAttribute('origin') == origin:
            f.write('\t\t'+origin+destination+'_'+message.getAttribute('name')+'_Opcode = ' + message.getAttribute('opcode') + ',\n');

    f.write('\t};\n}\n\n')  

    f.write('#endif // ' + fileDef)
    print('Done!')

def GenerateClassDefinition(f, Class, isStruct, origin, destination):

    fields = Class.getElementsByTagName('Field')

    send = 0
    prefix = destination+origin
    if origin == Class.getAttribute('origin'):
        send = 1
        prefix = origin+destination
    
    if isStruct:
        f.write('\tclass '+Class.getAttribute('name')+'\n')
    else:
        dest = 'Recv'
        if send:
            dest = 'Send'
        f.write('\tclass '+prefix+'_'+Class.getAttribute('name')+dest+' : public Packet\n')
        
    f.write('\t{\n')
    f.write('\t\tvoid Deserialize(ReadBuffer* pBuffer)\n')
    f.write('\t\t{\n')
    for field in fields:
        f.write('\t\t\t')
        Name = field.getAttribute('name')
        Type = field.getAttribute('type')
        if field.getAttribute('array') == '1':
            f.write('{\n')
            f.write('\t\t\t\tuint32_t length = 0;\n')
            f.write('\t\t\t\tpBuffer->Read_uint32(length);\n')
            
            f.write('\t\t\t\tfor(uint32_t i = 0; i < length; ++i)\n')
            f.write('\t\t\t\t{\n')
            f.write('\t\t\t\t\t'+Type+' entry;\n')
            if field.getAttribute('struct') == '1':
                f.write('\t\t\t\t\tentry.Deserialize(pBuffer);\n')
            else:
                f.write('\t\t\t\t\tpBuffer->Read_'+Type+'(entry);\n')
            f.write('\t\t\t\t\t'+Name+'.push_back(entry);\n')
            f.write('\t\t\t\t}\n')
                
            f.write('\t\t\t}\n')
            
        elif field.getAttribute('struct') == '1':
            f.write(Name+'.Deserialize(pBuffer);\n')
        else:    
            f.write('pBuffer->Read_'+Type+'('+Name+');\n')
    f.write('\t\t}\n\n')

    f.write('\t\tvoid Serialize(WriteBuffer* pBuffer)\n')
    f.write('\t\t{\n')
    if isStruct != 1:
        f.write('\t\t\tpBuffer->Write_uint16('+ prefix +'_' + Class.getAttribute('name') + '_Opcode);\n')
    for field in fields:
        f.write('\t\t\t')
        Name = field.getAttribute('name')
        Type = field.getAttribute('type')
        if field.getAttribute('array') == '1':
            f.write('{\n')
            
            f.write('\t\t\t\tpBuffer->Write_uint32(static_cast<uint32_t>('+ Name +'.size()));\n')
            
            f.write('\t\t\t\tfor(auto entry : ' + Name + ')\n')
            f.write('\t\t\t\t{\n')
            if field.getAttribute('struct') == '1':
                f.write('\t\t\t\t\tentry.Serialize(pBuffer);\n')
            else:
                f.write('\t\t\t\t\tpBuffer->Write_'+Type+'(entry);\n')
            f.write('\t\t\t\t}\n')
                
            f.write('\t\t\t}\n')
            
        elif field.getAttribute('struct') == '1':
            f.write(Name+'.Serialize(pBuffer);\n')
        else:    
            f.write('pBuffer->Write_'+Type+'('+Name+');\n')
            
    f.write('\t\t}\n\n')

    for field in fields:
        f.write('\t\t')
        Name = field.getAttribute('name')
        Type = field.getAttribute('type')
        if field.getAttribute('array') == '1':
            if field.getAttribute('struct') == '1':
                f.write('std::vector<'+ Type + '> ' + Name + ';\n')
            else:    
                f.write('std::vector<' + GetCppType(Type) + '> ' + Name + ';\n')
            
        elif field.getAttribute('struct') == '1':
            f.write(Type + ' ' + Name + ';\n')
        else:    
            f.write(GetCppType(Type) + ' ' + Name + ';\n')

    f.write('\t};\n\n')
        

def GenerateHandlerHeader(dom, output, origin, destination):
    filepath = os.path.join(output, destination + origin + '_Handler.h')

    print('Generating handler header', filepath,'...')
    
    f = open(filepath, 'w')
    f.write('// This file was generated, do not modify it !!!!  \n\n')
    fileDef = ('MSG_'+destination+'_'+origin+'_HANDLER_H\n').upper()
    f.write('#ifndef ' + fileDef)
    f.write('#define ' + fileDef)
    f.write('\n')
    f.write('#if defined(_MSC_VER) && (_MSC_VER >= 1200)\n')
    f.write('# pragma once\n')
    f.write('#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)\n\n')
    f.write('#include "PacketHandler.h"\n')
    f.write('#include "Packet.h"\n')
    f.write('#include <vector>\n')
    f.write('#include <string>\n')
    f.write('#include "' + origin + destination + '_Opcode.h"\n')
    f.write('#include "' + destination + origin + '_Opcode.h"\n\n\n')
    f.write('namespace Messages\n{\n')
    f.write('\tclass '+destination+origin+'_Handler : public PacketHandler\n\t{\n')
    f.write('\tpublic:\n\n')
    f.write('\t\tvoid HandleBuffer(ReadBuffer* pBuffer, uint16_t aOpcode, uint16_t aConnectionId);\n')
    f.write('\t};\n\n')

    structs = dom.getElementsByTagName('Struct')
    
    for struct in structs:
        GenerateClassDefinition(f, struct, 1, origin, destination)

    structs = dom.getElementsByTagName('Message')
    for struct in structs:
        GenerateClassDefinition(f, struct, 0, origin, destination)
    
    f.write('}\n\n')  

    f.write('#endif // ' + fileDef)
    print('Done!')

def GenerateHandlerSource(messages, output, origin, destination):
    filepath = os.path.join(output, destination + origin + '_Handler.cpp')

    print('Generating handler source', filepath,'...')
    
    f = open(filepath, 'w')
    f.write('// This file was generated, do not modify it !!!!  \n\n')
    f.write('#include "PacketHandler.h"\n')
    f.write('#include "' + destination + origin + '_Handler.h"\n\n\n')

    for message in messages:
        if message.getAttribute('origin') == destination:
            Name = message.getAttribute('name')
            f.write('extern void Handle' + destination + origin + '_' + Name + 'Recv(const Messages::' + destination + origin + '_' + Name + 'Recv& aMsg);\n') 

    
    f.write('\nnamespace Messages\n{\n')
    f.write('\tvoid ' + destination + origin + '_Handler::HandleBuffer(ReadBuffer* pBuffer, uint16_t aOpcode, uint16_t aConnectionId)\n')
    f.write('\t{\n')
    f.write('\t\tswitch(aOpcode)\n')
    f.write('\t\t{\n')
    for message in messages:
        if message.getAttribute('origin') == destination:
            Name = message.getAttribute('name')
            f.write('\t\t\tcase ' + destination + origin + '_' + Name + '_Opcode:\n\t\t\t{\n')
            f.write('\t\t\t\t' + destination + origin + '_' + Name + 'Recv msg;\n')
            f.write('\t\t\t\tmsg.connectionId = aConnectionId;\n')
            f.write('\t\t\t\tmsg.Deserialize(pBuffer);\n')
            f.write('\t\t\t\tHandle' + destination + origin + '_' + Name + 'Recv(msg);\n')
            f.write('\t\t\t\tbreak;\n\t\t\t}\n')
            
    f.write('\t\t}\n')
    f.write('\t}\n\n')
    f.write('}\n')
    
    print('Done!')

if len(sys.argv) <= 5:
    print('Not enough arguments')
else: 
    output = sys.argv[1]
    source = sys.argv[2]
    origin = sys.argv[3]
    destination = sys.argv[4]
    subdir = sys.argv[5]

    file = os.path.join(output, source)
    print('Generating message code from', origin, 'to', destination, 'from', file)

    tree = parse(file)
    root = tree.documentElement

    assert root.tagName == "Messages"

    messages = tree.getElementsByTagName('Message')

    GenerateOpcodes(messages, output + subdir, origin, destination)
    GenerateOpcodes(messages, output + subdir, destination, origin)
    
    GenerateHandlerHeader(tree, output + subdir, origin, destination)
    GenerateHandlerSource(messages, output + subdir, origin, destination)
