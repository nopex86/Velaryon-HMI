#ifndef UDPCODECBUILDER_H
#define UDPCODECBUILDER_H

// [
//     { "name": "chamber_pressure", "type": "double" },
//     { "name": "igniter_state", "type": "bool" },
//     { "name": "tank_pressure_raw", "type": "uint32" }
// ]


// enum class FieldType
// {
//     UInt32,
//     Double,
//     Bool
// };

// struct FieldDescriptor
// {
//     QString name;
//     FieldType type;
//     int offset;   // position dans la trame binaire
// };

// using FieldValue = std::variant<uint32_t, double, bool>;

// struct TelemetryFrame
// {
//     QVector<FieldValue> values;
//     uint64_t timestamp;
// };



// using FieldValue = std::variant<uint32_t, double, bool>;

// struct TelemetryFrame
// {
//     std::vector<FieldValue> values;
//     uint64_t timestamp;
// };

// // protocol_engine.hpp
// struct FieldDescriptor {
//     QString name;
//     QString type;       // "uint8", "int16", "float32", ...
//     double  scale{1.0};
//     double  offset{0.0};
//     bool    display{true};
//     QString unit;
//     QString group;
//     double  alarmHigh{std::numeric_limits<double>::max()};
//     double  alarmLow {std::numeric_limits<double>::lowest()};
// };

// struct FrameDescriptor {
//     uint8_t                   id;
//     QString                   name;
//     bool                      isRx;   // true = RX, false = TX
//     std::vector<FieldDescriptor> fields;
//     QString                   footerType; // "none", "crc16_ccitt", ...
// };


// class ProtocolEngine {
// public:
//     bool loadFromFile(const QString& path);

//     // Parse une trame brute → map nom_champ → valeur physique
//     // Retourne false si CRC invalide ou frame inconnue
//     bool parseFrame(const QByteArray& raw,
//                     QString& outName,
//                     QHash<QString, double>& outValues) const;

//     // Construit une trame TX à partir du nom et des valeurs
//     QByteArray buildFrame(const QString& frameName,
//                           const QHash<QString, QVariant>& values) const;

//     const std::vector<FrameDescriptor>& descriptors() const;

// private:
//     QHash<uint8_t, FrameDescriptor> m_frameById;
//     QHash<QString,  FrameDescriptor> m_frameByName;

//     double decodeField(const FieldDescriptor& f,
//                        QDataStream& stream) const;
//     void   encodeField(const FieldDescriptor& f,
//                      QDataStream& stream,
//                      const QVariant& val) const;
//     uint16_t crc16ccitt(const QByteArray& data) const;
// };






// // sensor_store.hpp
// class SensorStore {
// public:
//     using FrameData = QHash<QString, double>;

//     // Appelé depuis le worker thread (1 kHz)
//     void update(const QString& frameName, const FrameData& values) {
//         std::lock_guard lock(m_mutex);
//         m_back[frameName] = values;
//         m_dirty.store(true, std::memory_order_release);
//     }

//     // Appelé depuis le thread UI (60 Hz)
//     // Retourne true si nouvelles données disponibles
//     bool swapIfDirty(QHash<QString, FrameData>& out) {
//         if (!m_dirty.load(std::memory_order_acquire))
//             return false;
//         std::lock_guard lock(m_mutex);
//         std::swap(m_front, m_back);
//         m_dirty.store(false, std::memory_order_relaxed);
//         out = m_front;
//         return true;
//     }

// private:
//     std::mutex                  m_mutex;
//     std::atomic_bool            m_dirty{false};
//     QHash<QString, FrameData>   m_front, m_back;
// };




// class SensorViewModel : public QObject {
//     Q_OBJECT
//     Q_PROPERTY(double pChambre READ pChambre NOTIFY dataRefreshed)
//     // ... autres propriétés

// public:
//     explicit SensorViewModel(SensorStore* store, QObject* parent = nullptr)
//         : QObject(parent), m_store(store)
//     {
//         m_timer.setTimerType(Qt::PreciseTimer);
//         m_timer.setInterval(16); // ~60 Hz
//         connect(&m_timer, &QTimer::timeout,
//                 this,     &SensorViewModel::refresh);
//         m_timer.start();
//     }

// private slots:
//     void refresh() {
//         QHash<QString, SensorStore::FrameData> snapshot;
//         if (!m_store->swapIfDirty(snapshot)) return;

//         // Appliquer alarmes, scaling cosmétique, etc.
//         m_pChambre = snapshot["SENSORS_MAIN"]["P_chambre"];
//         // ...
//         emit dataRefreshed();
//     }

// signals:
//     void dataRefreshed();

// private:
//     SensorStore* m_store;
//     QTimer       m_timer;
//     double       m_pChambre{0.0};
// };









// QTimer::start(20); // 50 Hz

// enum class FieldType
// {
//     UInt32,
//     UInt64,
//     Float,
//     Double,
//     Bool
// };



// struct FieldDescriptor
// {
//     QString name;
//     FieldType type;
//     int offset;
//     double scale = 1.0;
// };


// struct ProtocolDescription
// {
//     int version;
//     bool littleEndian;
//     int frameSize;
//     std::vector<FieldDescriptor> fields;
// };



// class FrameDecoder
// {
// public:
//     FrameDecoder(const ProtocolDescription& proto)
//         : m_proto(proto) {}

//     TelemetryFrame decode(const QByteArray& data);

// private:
//     ProtocolDescription m_proto;
// };


// using FieldValue =
//     std::variant<uint32_t, uint64_t, float, double, bool>;

#endif // UDPCODECBUILDER_H
