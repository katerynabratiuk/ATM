#pragma once

enum class Exceptions
{
	TooManyAttempts,
	DoesntExist,
	NoSuchCash,
	NotEnoughMoney,
	SamePassword,
	SameCard,
	AccessDenied
};

enum class DBExceptions {
	DatabaseError,
	ConnectionError,
	RecordNotFound
};