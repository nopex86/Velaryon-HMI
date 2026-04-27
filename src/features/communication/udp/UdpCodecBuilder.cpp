// TelemetryFrame FrameDecoder::decode(const QByteArray& data)
// {
//     TelemetryFrame frame;

//     for (const auto& field : m_fields)
//     {
//         switch (field.type)
//         {
//         case FieldType::UInt32:
//             frame.values.push_back(readUint32(data, field.offset));
//             break;

//         case FieldType::Double:
//             frame.values.push_back(readDouble(data, field.offset));
//             break;

//         case FieldType::Bool:
//             frame.values.push_back(readBool(data, field.offset));
//             break;
//         }
//     }

//     return frame;
// }

// int main(...)
// {
//     ProtocolDescription proto =
//         loadProtocol("protocol.json");

//     FrameDecoder decoder(proto);

//     UdpReceiver receiver;

//     QObject::connect(&receiver,
//                      &UdpReceiver::frameReceived,
//                      [&](const QByteArray& data)
//                      {
//                          auto frame = decoder.decode(data);
//                          telemetryModel.push(frame);
//                      });

//     ...
// }

// TelemetryFrame FrameDecoder::decode(
//     const QByteArray& data)
// {
//     TelemetryFrame frame;
//     frame.values.reserve(m_proto.fields.size());

//     for (const auto& field : m_proto.fields)
//     {
//         const char* ptr = data.constData() + field.offset;

//         switch (field.type)
//         {
//         case FieldType::UInt32:
//         {
//             uint32_t value =
//                 *reinterpret_cast<const uint32_t*>(ptr);
//             frame.values.push_back(value * field.scale);
//             break;
//         }

//         case FieldType::UInt64:
//         {
//             uint64_t value =
//                 *reinterpret_cast<const uint64_t*>(ptr);
//             frame.values.push_back(value);
//             break;
//         }

//         case FieldType::Float:
//         {
//             float value =
//                 *reinterpret_cast<const float*>(ptr);
//             frame.values.push_back(value * field.scale);
//             break;
//         }

//         case FieldType::Double:
//         {
//             double value =
//                 *reinterpret_cast<const double*>(ptr);
//             frame.values.push_back(value);
//             break;
//         }

//         case FieldType::Bool:
//         {
//             bool value = (*ptr != 0);
//             frame.values.push_back(value);
//             break;
//         }
//         }
//     }

//     return frame;
// }

// ProtocolDescription loadProtocol(const QString& path)
// {
//     QFile file(path);
//     file.open(QIODevice::ReadOnly);

//     auto doc = QJsonDocument::fromJson(file.readAll());
//     auto root = doc.object();

//     ProtocolDescription proto;

//     proto.version = root["version"].toInt();
//     proto.littleEndian = root["endianness"].toString() == "little";
//     proto.frameSize = root["frame_size"].toInt();

//     auto fieldsArray = root["fields"].toArray();

//     for (const auto& f : fieldsArray)
//     {
//         auto obj = f.toObject();

//         FieldDescriptor field;
//         field.name = obj["name"].toString();
//         field.offset = obj["offset"].toInt();
//         field.scale = obj.contains("scale")
//                           ? obj["scale"].toDouble()
//                           : 1.0;

//         QString typeStr = obj["type"].toString();

//         if (typeStr == "uint32")
//             field.type = FieldType::UInt32;
//         else if (typeStr == "uint64")
//             field.type = FieldType::UInt64;
//         else if (typeStr == "float")
//             field.type = FieldType::Float;
//         else if (typeStr == "double")
//             field.type = FieldType::Double;
//         else if (typeStr == "bool")
//             field.type = FieldType::Bool;
//         else
//             throw std::runtime_error("Unknown field type");

//         proto.fields.push_back(field);
//     }

//     return proto;
// }



// // udp_worker.cpp — onReadyRead
// void UdpWorker::onReadyRead() {
//     while (m_socket->hasPendingDatagrams()) {
//         QByteArray buf(m_socket->pendingDatagramSize(), Qt::Uninitialized);
//         m_socket->readDatagram(buf.data(), buf.size());

//         // 1. Log RAW immédiatement — jamais de perte
//         m_logger->logRaw(buf);

//         // 2. Parse
//         QString name;
//         QHash<QString, double> values;
//         if (m_engine->parseFrame(buf, name, values))
//             m_store->update(name, values); // lock-free via atomic swap
//     }
// }
