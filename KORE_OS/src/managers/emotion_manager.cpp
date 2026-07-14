#include <Arduino.h>
#include "emotion_manager.h"

static const char* const kw_extrahappy[] = {
    "approved", "accepted", "achievement", "awesome", "bonus",
    "completed", "complete", "confirmed", "congratulations",
    "congrats", "excellent", "gift", "good", "great", "happy",
    "improved", "nice", "promotion", "promoted", "reward",
    "success", "successful", "winner", "won", "yes", "party",
    "aceito", "alegria", "aprovado", "boa noticia",
    "confirmado", "concluido", "excelente", "feliz", "ganhou",
    "ganhador", "legal", "melhorou", "otimo", "parabens",
    "presente", "promocao", "recompensa", "sim", "sucesso",
    "vitoria", "festa"
};

static const char* const kw_loving[] = {
    "affection", "baby", "boyfriend", "darling", "dear",
    "family", "girlfriend", "heart", "hug", "husband",
    "kiss", "love", "lovely", "miss you", "mom", "dad",
    "daughter", "son", "sweet",
    "abraco", "amor", "beijo", "carinho", "esposa", "esposo",
    "familia", "filha", "filho", "mae", "pai",
    "querida", "querido", "saudades", "te adoro", "te amo"
};

static const char* const kw_sad[] = {
    "bill", "blocked", "cancel", "cancelled", "charge",
    "declined", "debt", "denied", "error", "expired",
    "failed", "failure", "invoice", "issue", "late",
    "lost", "overdue", "payment", "problem", "rejected",
    "suspended", "unavailable", "warning",
    "atrasado", "bloqueado", "boleto", "cancelado",
    "cobranca", "conta", "divida", "erro", "falha",
    "falhou", "fatura", "indisponivel", "negado",
    "pagamento", "perdeu", "problema", "recusado",
    "rejeitado", "suspenso", "vencido"
};

static const char* const kw_surprise[] = {
    "alert", "announcement", "attention", "breaking",
    "immediately", "important", "new", "news", "now",
    "today", "unexpected", "update", "urgent",
    "acabou", "acabou de", "agora", "alerta", "atencao",
    "hoje", "importante", "imediatamente", "novidade",
    "novo", "noticia", "surpresa", "urgente", "ultima hora"
};

static const char* const kw_confused[] = {
    "confused", "hmm", "how", "maybe", "perhaps",
    "really", "strange", "unknown", "unsure", "weird",
    "what", "why",
    "como", "como assim", "confuso", "estranho",
    "esquisito", "hein", "humm", "nao sei", "onde",
    "porque", "quem", "quando", "talvez"
};

#define COUNT(arr) (sizeof(arr) / sizeof(arr[0]))

static const EmotionRule emotionRules[] = {
    { FACE_EXTRA_HAPPY, 5000, 1, COUNT(kw_extrahappy), kw_extrahappy },
    { FACE_LOVING,      5000, 2, COUNT(kw_loving),     kw_loving },
    { FACE_SAD,         5000, 3, COUNT(kw_sad),        kw_sad },
    { FACE_SURPRISE,    5000, 4, COUNT(kw_surprise),   kw_surprise },
    { FACE_CONFUSED,    5000, 2, COUNT(kw_confused),   kw_confused },
};

static const uint8_t emotionCount = COUNT(emotionRules);

#undef COUNT

FaceType detectEmotion(String text)
{
    text.toLowerCase();
    int bestScore = 0;
    int bestPriority = 0;
    FaceType bestFace = FACE_HAPPY;

    for (uint8_t i = 0; i < emotionCount; i++)
    {
        const EmotionRule &rule = emotionRules[i];
        int score = 0;

        for (uint8_t k = 0; k < rule.keywordCount; k++)
        {
            if (text.indexOf(rule.keywords[k]) >= 0)
            {
                score++;
            }
        }

        if (score > bestScore)
        {
            bestScore = score;
            bestPriority = rule.priority;
            bestFace = rule.face;
        }
        else if (score == bestScore && score > 0 && rule.priority > bestPriority)
        {
            bestPriority = rule.priority;
            bestFace = rule.face;
        }
    }

    return bestFace;
}

bool loadEmotionRules()
{
    return true;
}

FaceType emotionNameToFace(String name)
{
    name.toLowerCase();
    if (name == "happy")      return FACE_HAPPY;
    if (name == "extrahappy") return FACE_EXTRA_HAPPY;
    if (name == "sad")        return FACE_SAD;
    if (name == "sleep")      return FACE_SLEEP;
    if (name == "surprise")   return FACE_SURPRISE;
    if (name == "loving")     return FACE_LOVING;
    if (name == "confused")   return FACE_CONFUSED;
    if (name == "demon")      return FACE_DEMON;
    return FACE_HAPPY;
}
