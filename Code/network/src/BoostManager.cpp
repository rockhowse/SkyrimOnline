#include "BoostManager.h"
#include "BoostConnection.h"
#include "dh.h"
#include "osrng.h"

class KeyAgreement : public IKeyAgreement
{
public:

	KeyAgreement()
	{
		CryptoPP::Integer p("0xB10B8F96A080E01DDE92DE5EAE5D54EC52C99FBCFB06A3C6"
			"9A6A9DCA52D23B616073E28675A23D189838EF1E2EE652C0"
			"13ECB4AEA906112324975C3CD49B83BFACCBDD7D90C4BD70"
			"98488E9C219A73724EFFD6FAE5644738FAA31A4FF55BCCC0"
			"A151AF5F0DC8B4BD45BF37DF365C1A65E68CFDA76D4DA708"
			"DF1FB2BC2E4A4371");

		CryptoPP::Integer g("0xA4D1CBD5C3FD34126765A442EFB99905F8104DD258AC507F"
			"D6406CFF14266D31266FEA1E5C41564B777E690F5504F213"
			"160217B4B01B886A5E91547F9E2749F4D7FBD7D3B9A92EE1"
			"909D0D2263F80A76A6A24C087A091F531DBF0A0169B6A28A"
			"D662A4D18E73AFA32D779D5918D08BC8858F4DCEF97C2A24"
			"855E6EEB22B3B2E5");

		CryptoPP::Integer q("0xF518AA8781A8DF278ABA4E7D64B7CB9D49462353");

		CryptoPP::AutoSeededRandomPool rnd;

		m_diffieContext.AccessGroupParameters().Initialize(p, q, g);
		m_privateKey.resize(m_diffieContext.PrivateKeyLength());
		m_publicKey.resize(m_diffieContext.PublicKeyLength());

		m_diffieContext.GenerateKeyPair(rnd, m_privateKey, m_publicKey);
	}

	void Serialize(std::string& aBuffer)
	{
		aBuffer.append((const char*)m_publicKey.BytePtr(), m_publicKey.SizeInBytes());
	}

	std::string Agree(ReadBuffer* apBuffer)
	{
		std::string sharedSecret(m_diffieContext.AgreedValueLength(), '\0');

		CryptoPP::SecByteBlock remotePublicKey(128);

		apBuffer->ReadRaw(remotePublicKey.BytePtr(), 128);

		if (m_diffieContext.Agree((uint8_t*)&sharedSecret[0], m_privateKey, remotePublicKey))
		{
			return sharedSecret;
		}

		return std::string();
	}
private:

	CryptoPP::DH m_diffieContext;
	CryptoPP::SecByteBlock m_privateKey;
	CryptoPP::SecByteBlock m_publicKey;
};

BoostManager::IOPool::IOPool()
	: m_ioService()
	, m_work(m_ioService)
{
	m_thread = new boost::thread(boost::bind(&boost::asio::io_service::run, &m_ioService));
}

BoostManager::IOPool::~IOPool()
{
	try
	{
		m_ioService.stop();
		m_thread->join();
		delete m_thread;
	}
	catch (boost::thread_interrupted&)
	{

	}
}

BoostManager& BoostManager::GetInstance()
{
	static BoostManager instance;
	return instance;
}

BoostManager::BoostManager()
	: m_pools(nullptr)
	, m_poolCount(0)
	, m_poolCursor(0)
	, m_pKeyAgreement(new KeyAgreement)
{

}

BoostManager::~BoostManager()
{
	BoostManager::GetInstance().m_poolCount = 0;
	BoostManager::GetInstance().m_poolCursor = 0;
	delete[] BoostManager::GetInstance().m_pools;
}

boost::asio::io_service& BoostManager::GetIoService()
{
	m_poolCursor += 1;

	if (m_poolCursor >= m_poolCount)
	{
		m_poolCursor = 0;
	}

	return m_pools[m_poolCursor].m_ioService;
}

void BoostManager::Setup(uint32_t aThreadCount)
{
	BoostManager::GetInstance().m_poolCount = std::max(aThreadCount, (uint32_t)1);
	BoostManager::GetInstance().m_poolCursor = 0;
	BoostManager::GetInstance().m_pools = new IOPool[BoostManager::GetInstance().m_poolCount];
}

void BoostManager::Destroy()
{
	BoostManager::GetInstance().m_poolCount = 0;
	BoostManager::GetInstance().m_poolCursor = 0;
	delete[] BoostManager::GetInstance().m_pools;
	BoostManager::GetInstance().m_pools = nullptr;
}