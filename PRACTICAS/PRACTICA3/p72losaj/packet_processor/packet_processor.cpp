#include "packet_processor.hpp"

PacketProcessor::PacketProcessor(size_t size)
{
   //TODO

    tam = size;

}

Response 
PacketProcessor::process(const Packet &packet)
{
    //TODO

//Cuando llega un paquete:
//
// 1. quitaremos de la cola todos los que llegaron antes y que
//    ya han sido procesados.
// 2. Si no hay espacio en la cola, este paquete será dropped y termina
//    su procesado retornando Response(true, 0).
// 3. Sino
// 3.1 Si la cola está vacía, el paquete será procesado inmediatamente
//     retornando Response(false, tiempo de llegada)
// 3.2 Sino será encolado y su tiempo de inicio de proceso será 
//     por lo tanto el tiempo finalización del procesado del
//     último paquete encolado retornando 
//     Response(false, tiempo de finalización del último paquete).
//
// Cuestión: En la cola, ¿qué encolamos?; el tiempo de llegada o 
// el tiempo de finalización.

    while( (cola.front() <= packet.arrival_time) && (cola.is_empty() == false ) ) cola.deque();
    

    if(cola.is_empty() == true )
    {
        int valor = packet.arrival_time + packet.process_time;
        cola.enque(valor);
        return Response(false, packet.arrival_time);
    }

    // Cola llena

    // Sin espacios en la cola

    else if( cola.size() == tam) return Response(true, 0);

    // Con espacio en la cola
    
    else
    {
        
        int valor = cola.back();
        cola.enque(valor + packet.process_time);
        return Response(false, valor);

    }
    

    return Response(true, 0);

    
    
    
}


/** @brief process the packets and generate a response for each of them.*/
std::vector <Response>
process_packets(const std::vector <Packet> &packets,
                PacketProcessor& p)
{
    std::vector <Response> responses;
    for (size_t i = 0; i < packets.size(); ++i)
        responses.push_back(p.process(packets[i]));
    return responses;
}

/** @brief print the processing start times for the packets.*/
std::ostream&
write_responses(std::ostream &out, const std::vector <Response> &responses)
{
    for (size_t i = 0; i < responses.size(); ++i)
        out << (responses[i].dropped ? -1 : responses[i].start_time) << std::endl;
    return out;
}
