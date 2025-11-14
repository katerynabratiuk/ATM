#pragma once

enum class Exceptions
{
	TooManyAttempts,
	NoSuchCash,
	NotEnoughMoney,
	SamePassword,
	SameCard,
	AccessDenied,
	DatabaseError,
	ConnectionError,
	RecordNotFound
};