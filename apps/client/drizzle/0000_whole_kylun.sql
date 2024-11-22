CREATE TABLE IF NOT EXISTS "updates" (
	"id" uuid PRIMARY KEY NOT NULL,
	"temperature" real NOT NULL,
	"humidity" real NOT NULL,
	"power1" boolean NOT NULL,
	"power2" boolean NOT NULL,
	"created_at" timestamp DEFAULT now() NOT NULL,
	"udpated_at" timestamp (3) DEFAULT now() NOT NULL
);
