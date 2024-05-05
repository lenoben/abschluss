import { PrismaClient } from "@prisma/client";
const prisma = new PrismaClient();


const saveError = async (errname: any, errmsg: any) => {
    await prisma.error_log.create({ data: {
        name: errname,
        message: errmsg,
        user_id: 1
    }})
}

export { saveError};