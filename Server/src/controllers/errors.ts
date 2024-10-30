import { PrismaClient } from "@prisma/client";
const prisma = new PrismaClient();

const saveError = async (errname: any, errmsg: any) => {
  await prisma.error_log.create({
    data: {
      name: errname,
      message: errmsg,
      user_id: "66b393083821775e2b731015",
    },
  });
};

export { saveError };
