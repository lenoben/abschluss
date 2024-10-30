import { PrismaClient } from '@prisma/client';

const prisma = new PrismaClient();

interface SaveText {
    user: string;
    type: string;
    result: string;
    probability: number;
}

const getIndexForm = async (userid: string) => {
    try {
        const data = await prisma.model_text.findMany({
            select: {
                site_user: {
                    select: {
                        name: true,
                    },
                },
                content: true,
                random_forest: {
                    select: {
                        result: true,
                        probability: true,
                    },
                },
                nmc: {
                    select: {
                        result: true,
                    },
                },
                logreg: {
                    select: {
                        result: true,
                        probability: true,
                    },
                },
                ffn: {
                    select: {
                        result: true,
                    },
                },
            },
            where: {
                site_user: {
                    id: userid,
                },
            },
            take: 50,
            orderBy: {
                id: 'desc',
            },
        });
        return data;
    } catch (error) {
        console.error('Error in getIndexForm:', error);
        throw error;
    }
};

const getIndex = async () => {
    try {
        const data = await prisma.model_text.findMany({
            select: {
                content: true,
            },
        });
        return data;
    } catch (error) {
        console.error('Error in getIndex:', error);
        throw error;
    }
};

const getExisting = async (text: string, id: string) => {
    try {
        // Try to find an existing model_text record with the same content and user_id
        const existingModelText = await prisma.model_text.findFirst({
            where: {
                content: text,
                user_id: id,
            },
        });

        // If an existing record is found, return its id
        if (existingModelText !== null) {
            const modelTextId = existingModelText.id;
            return modelTextId;
        }

        // If no existing record is found, create a new one
        // Create a new model_text record
        const modelText = await prisma.model_text.create({
            data: {
                content: text,
                user_id: id,
            },
        });

        // Return the id of the newly created model_text record
        const modelTextId = modelText.id;
        return modelTextId;
    } catch (error) {
        console.error('Error in getExisting:', error);
        throw error;
    }
};

const saveText = async (context: SaveText, text: string) => {
    try {
        // Create a new model_text record
        const id = await getExisting(text, '66b393083821775e2b731015');

        const resint = parseInt(context.result);

        if (context.type === 'nmc') {
            await prisma.nmc.create({
                data: {
                    result: resint,
                    text_id: id,
                },
            });
        } else if (context.type === 'logreg') {
            await prisma.logreg.create({
                data: {
                    text_id: id,
                    probability: context.probability,
                    result: resint,
                },
            });
        }
    } catch (error) {
        console.error('Error in saveText:', error);
        throw error;
    }
};

// Ensure that the Prisma client connection is closed when the application terminates
process.on('beforeExit', async () => {
    await prisma.$disconnect();
});

export { prisma, getIndexForm, getIndex, saveText, SaveText };
