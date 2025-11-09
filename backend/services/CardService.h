#include "backend/services/ICardService.h"
#include "backend/repositories/ICardRepository.h"

class CardService : public ICardService
{
public:
	CardService(ICardRepository& cardRepository) : _cardRepository(cardRepository){};

private:
	ICardRepository& _cardRepository;
	void doAuth(const std::string& cardNum, const std::string& pin);
	void doDeposit(const std::string& cardNum, int amount);
	void doWithdraw(const std::string& cardNum, int amount);
	void doTransfer(const std::string& from, const std::string& to, int amount);
	void doChangePin(const std::string& cardNum, const std::string& newPin);
	Card doGetCard(const std::string& cardNum);
};